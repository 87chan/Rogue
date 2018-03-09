// Fill out your copyright notice in the Description page of Project Settings.

#include "MapManager.h"
#include "Rogue.h"
#include "Engine/StaticMesh.h"
#include "Engine/StaticMeshActor.h"

AMapManager::AMapManager(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
	, Width(10)
	, Height(10)
	, bCreatedMap(false)
	, DefaultEnemyNum(0)
	, WallClass(nullptr)
	, GoalClass(nullptr)
	, EnemyClass(nullptr)
{
	TArray<FFieldInfo> FieldInfo;
	FieldInfo.Init(FFieldInfo(), Width);
	FieldArray.Init(FieldInfo, Height);
}

void AMapManager::CreateMap()
{
	// Surround Wall.
	for (int32 i = 0; i < Height; ++i)
	{
		for (int32 j = 0; j < Width; ++j)
		{
			bool bSurround = ((i == 0) || (i == Height - 1) || (j == 0) || (j == Width - 1));
			EFieldType Type = (bSurround) ? EFieldType::Fld_Wall : EFieldType::FldGrp_BottomLayer;

			if (bSurround)
			{
				this->SpawnActor(WallClass, FVector2D(j, i), Type);
			}
			else
			{
				this->FieldTypeSet(FVector2D(j, i), Type);
			}
		}
	}

	bCreatedMap = true;
	
	// Goal.
	FVector2D GoalArrayLoc = this->GetRandomArrayLocation();
	this->SpawnActor(GoalClass, GoalArrayLoc, EFieldType::Fld_Goal);

	for (int32 i = 0; i < DefaultEnemyNum; ++i)
	{
		FVector2D EnemyArrayLoc = this->GetRandomArrayLocation();
		this->SpawnActor(EnemyClass, EnemyArrayLoc, EFieldType::Fld_Enemy);
	}
}

FVector2D AMapManager::GetOffset() const
{
	FVector2D Offset = FVector2D::ZeroVector;

	if (Width % 2 == 0)
	{
		Offset.Y += Rogue::Unit * Width * 0.5f;
		Offset.Y -= Rogue::Unit * 0.5f;
	}
	else if (Width != 1)
	{
		Offset.Y += Rogue::Unit * (Width - 1) * 0.5f;
	}

	if (Height % 2 == 0)
	{
		Offset.X -= Rogue::Unit * Height * 0.5f;
		Offset.X += Rogue::Unit * 0.5f;
	}
	else if (Height != 1)
	{
		Offset.X -= Rogue::Unit * (Height - 1) * 0.5f;
	}

	return Offset;
}

FVector2D AMapManager::GetRandomArrayLocation() const
{
	if (!bCreatedMap) return FVector2D::ZeroVector;

	int32 X = 0;
	int32 Y = 0;

	if (0 < FieldArray.Num())
	{
		while ((FieldArray[Y][X].Type & EFieldType::FldGrp_TopLayer) != EFieldType::Fld_None)
		{
			X = FMath::Rand() % Width;
			Y = FMath::Rand() % Height;
		}
	}

	return FVector2D((float)X, (float)Y);
}

bool AMapManager::IsPossibleMove(const FVector2D& ArrayLocation) const
{
	EFieldType Type = FieldArray[(int32)ArrayLocation.Y][(int32)ArrayLocation.X].Type;
	return ((Type & EFieldType::FldGrp_TopLayer) == EFieldType::Fld_None);
}

AActor* AMapManager::SpawnActor(UClass* Class, const FVector2D& ArrayLocation, EFieldType Type)
{
	FTransform Transform = FTransform(FVector(-Rogue::Unit * ArrayLocation.Y, Rogue::Unit * ArrayLocation.X, 0.0f));
	AActor* Actor = this->GetWorld()->SpawnActor<AActor>(Class, Transform);
	check(Actor);

	this->FieldTypeSet(ArrayLocation, Type);

	return Actor;
}

void AMapManager::FieldTypeSet(const FVector2D& ArrayLocation, EFieldType Type)
{
	FieldArray[(int32)ArrayLocation.Y][(int32)ArrayLocation.X].Type |= Type;
}