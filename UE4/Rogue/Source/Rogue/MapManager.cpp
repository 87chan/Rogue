// Fill out your copyright notice in the Description page of Project Settings.

#include "MapManager.h"
#include "Rogue.h"
#include "Engine/StaticMesh.h"
#include "Engine/StaticMeshActor.h"
#include "RoguePawn.h"
#include "RogueUtility.h"

AMapManager::AMapManager(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
	, Width(10)
	, Height(10)
	, bCreatedMap(false)
	, DefaultEnemyNum(0)
	, WallClass(nullptr)
	, GoalClass(nullptr)
	, EnemyClass(nullptr)
	, EnemyManager(nullptr)
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
			EFieldType Type = (bSurround) ? EFieldType::Wall : EFieldType::Grp_BottomLayer;

			if (bSurround)
			{
				this->SpawnActor(WallClass, FVector2D(i, j), Type);
			}
			else
			{
				this->FieldTypeSet(FVector2D(i, j), Type);
			}
		}
	}

	bCreatedMap = true;
	
	// Goal.
	FVector2D GoalArrayLoc = this->GetRandomArrayLocation();
	this->SpawnActor(GoalClass, GoalArrayLoc, EFieldType::Goal);

	for (int32 i = 0; i < DefaultEnemyNum; ++i)
	{
		FVector2D EnemyArrayLoc = this->GetRandomArrayLocation();
		this->SpawnActor(EnemyClass, EnemyArrayLoc, EFieldType::Enemy);
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
		while ((FieldArray[Y][X].FieldType & EFieldType::Grp_TopLayer) != EFieldType::None)
		{
			X = FMath::Rand() % Width;
			Y = FMath::Rand() % Height;
		}
	}

	return FVector2D((float)X, (float)Y);
}

bool AMapManager::IsPossibleMove(const FVector2D& ArrayLocation) const
{
	EFieldType Type = FieldArray[(int32)ArrayLocation.Y][(int32)ArrayLocation.X].FieldType;
	return ((Type & EFieldType::Grp_TopLayer) == EFieldType::None);
}

const FEffectInfo AMapManager::GetEffectInfo(const FVector2D& InArrayLocation, int32 Index) const
{
	FEffectInfo Info = FEffectInfo();

	if (Index <= FieldArray[(int32)InArrayLocation.Y][(int32)InArrayLocation.X].EffectList.Num() - 1)
	{
		Info = FieldArray[(int32)InArrayLocation.Y][(int32)InArrayLocation.X].EffectList[Index];
	}

	return Info;
}

void AMapManager::Consume(const FVector2D& InArrayLocation, int32 Index)
{
	if (Index <= FieldArray[(int32)InArrayLocation.Y][(int32)InArrayLocation.X].EffectList.Num() - 1)
	{
		FieldArray[(int32)InArrayLocation.Y][(int32)InArrayLocation.X].EffectList.RemoveAt(Index);
	}
}

bool AMapManager::CheckExist(const FVector2D& InArrayLocation, EFieldType Type)
{
	if (InArrayLocation.X < 0 || Width <= InArrayLocation.X) return false;
	if (InArrayLocation.Y < 0 || Height <= InArrayLocation.Y) return false;

	if ((FieldArray[(int32)InArrayLocation.Y][(int32)InArrayLocation.X].FieldType & Type) != EFieldType::None)
	{
		return true;
	}

	return false;
}

bool AMapManager::CheckAdjacent(const FVector2D& InArrayLocation, EFieldType Type)
{
	for (int32 i = 0; i < (int32)EDirection_Type::Num; ++i)
	{
		if (CheckExist(InArrayLocation + RogueUtility::GetDirection(static_cast<EDirection_Type>(i)), Type)) return true;
	}

	return false;
}

void AMapManager::ChangeFieldType(const FVector2D& PrevArrayLoc, const FVector2D& NextArrayLoc, EFieldType Type)
{
	FieldArray[(int32)PrevArrayLoc.Y][(int32)PrevArrayLoc.X].FieldType &= ~Type;
	FieldArray[(int32)NextArrayLoc.Y][(int32)NextArrayLoc.X].FieldType |= Type;
}

const FVector2D AMapManager::Search(EFieldType Type) const
{
	for (int32 i = 0; i < Height; ++i)
	{
		for (int32 j = 0; j < Width; ++j)
		{
			if ((FieldArray[i][j].FieldType & Type) != EFieldType::None)
			{
				return FVector2D((float)j, (float)i);
			}
		}
	}

	return FVector2D::ZeroVector;
}

void AMapManager::Search(EEffectType Type, FApplyEffectList& OutList) const
{
	for (int32 i = 0; i < Height; ++i)
	{
		for (int32 j = 0; j < Width; ++j)
		{
			TArray<FEffectInfo> InfoList = FieldArray[i][j].EffectList;
			if (0 != InfoList.Num())
			{
				for (int32 k = 0; k < InfoList.Num(); ++k)
				{
					if ((InfoList[k].EffectType & Type) != EEffectType::None)
					{
						FApplyEffectInfo ApplyInfo = FApplyEffectInfo();
						ApplyInfo.ArrayLocation = FVector2D((float)j, (float)i);
						ApplyInfo.Index = k;
						OutList.Add(ApplyInfo);
					}
				}
			}
		}
	}
}

AActor* AMapManager::SpawnActor(UClass* Class, const FVector2D& ArrayLocation, EFieldType Type)
{
	FTransform Transform = FTransform(FVector(-Rogue::Unit * ArrayLocation.Y, Rogue::Unit * ArrayLocation.X, 0.0f));
	FActorSpawnParameters Params;
	Params.bNoFail = true;
	Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	AActor* Actor = this->GetWorld()->SpawnActor<AActor>(Class, Transform, Params);
	check(Actor);

	this->FieldTypeSet(ArrayLocation, Type);
	if (ARoguePawn* RoguePawn = Cast<ARoguePawn>(Actor))
	{
		RoguePawn->ArrayLocation = ArrayLocation;
	}

	return Actor;
}

void AMapManager::FieldTypeSet(const FVector2D& ArrayLocation, EFieldType Type)
{
	FieldArray[(int32)ArrayLocation.Y][(int32)ArrayLocation.X].FieldType |= Type;
}

void AMapManager::EffectInfoSet(const FVector2D& ArrayLocation, FEffectInfo Info)
{
	FieldArray[(int32)ArrayLocation.Y][(int32)ArrayLocation.X].EffectList.Add(Info);
}
