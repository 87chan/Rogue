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
	, WallClass(nullptr)
	, GoalClass(nullptr)
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
			FieldArray[i][j] = FFieldInfo((bSurround) ? EFieldType::Fld_Wall : EFieldType::Fld_Floor);

			if (bSurround)
			{
				this->SpawnActor(WallClass, FVector2D(j, i));
			}
		}
	}

	bCreatedMap = true;
	
	// Goal.
	FVector2D GoalArrayLoc = this->GetRandomArrayLocation();
	this->SpawnActor(GoalClass, GoalArrayLoc);
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
		while ((FieldArray[Y][X].Type & EFieldType::Fld_Floor) != EFieldType::Fld_Floor)
		{
			X = FMath::Rand() % Width;
			Y = FMath::Rand() % Height;
		}
	}

	return FVector2D((float)X, (float)Y);
}

bool AMapManager::IsPossibleMove(FVector2D ArrayLocation) const
{
	EFieldType Type = FieldArray[(int32)ArrayLocation.Y][(int32)ArrayLocation.X].Type;
	return ((Type & EFieldType::Fld_Floor) == EFieldType::Fld_Floor);
}

AActor* AMapManager::SpawnActor(UClass* Class, FVector2D ArrayLocation)
{
	FTransform Transform = FTransform(FVector(-Rogue::Unit * ArrayLocation.X, Rogue::Unit * ArrayLocation.Y, 0.0f));
	AActor* Actor = this->GetWorld()->SpawnActor<AActor>(Class, Transform);
	check(Actor);

	return Actor;
}