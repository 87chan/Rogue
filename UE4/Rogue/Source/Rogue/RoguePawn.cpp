// Fill out your copyright notice in the Description page of Project Settings.

#include "RoguePawn.h"
#include "Rogue.h"
#include "Components/StaticMeshComponent.h"
#include "RogueUtility.h"
#include "MapManager.h"

ARoguePawn::ARoguePawn(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
	, MapManager(nullptr)
	, ArrayLocation(FVector2D::ZeroVector)
	, Direction(EDirection_Type::Dir_None)
	, MaxLifePoint()
	, LeftLifePoint()
	, RiskPoint()
	, BaseAttack()
	, BaseDeffence()
{
	MaxLifePoint = 100;
	LeftLifePoint = MaxLifePoint;
	BaseAttack = 15;
	BaseDeffence = 5;
}

void ARoguePawn::BeginPlay()
{
	Super::BeginPlay();

	Direction = RogueUtility::GetRandomDirection();
	this->Turn(Direction);
}

bool ARoguePawn::CheckAdjacent(EFieldType Type)
{
	if (MapManager)
	{
		return MapManager->CheckAdjacent(ArrayLocation, Type);
	}

	return false;
}

void ARoguePawn::Turn(EDirection_Type DirType)
{
	if (DirType != EDirection_Type::Dir_None)
	{
		Direction = DirType;
		RootComponent->SetRelativeRotation(RogueUtility::GetRotation(DirType));
	}
}

void ARoguePawn::AdjustLocation(FVector2D InArrayLocation)
{
	MapManager->ChangeFieldType(ArrayLocation, InArrayLocation, this->GetFieldType());

	ArrayLocation = InArrayLocation;

	FVector2D Location = FVector2D::ZeroVector;
	Location.X = -ArrayLocation.Y * Rogue::Unit;
	Location.Y = ArrayLocation.X * Rogue::Unit;

	this->SetActorLocation(FVector(Location.X, Location.Y, 0.0f));
}

void ARoguePawn::Attack()
{
	FVector2D AttackArrayLocation = ArrayLocation + RogueUtility::GetDirection(Direction);

	FEffectInfo Info = FEffectInfo(this->GetAttackType(), BaseAttack);

	MapManager->EffectInfoSet(AttackArrayLocation, Info);
}

void ARoguePawn::ApplyDamage(EEffectType ApplyEffect)
{
	if (MapManager)
	{
		FApplyEffectList ApplyEffectList;
		MapManager->Search(ApplyEffect, ApplyEffectList);

		ApplyEffectList.Sort([](const FApplyEffectInfo& Info1, const FApplyEffectInfo& Info2) {
			return Info1.Index > Info2.Index;
		});

		for (FApplyEffectInfo ApplyEffectInfo : ApplyEffectList)
		{
			if (ArrayLocation == ApplyEffectInfo.ArrayLocation)
			{
				const FEffectInfo EffectInfo = MapManager->GetEffectInfo(ApplyEffectInfo.ArrayLocation, ApplyEffectInfo.Index);
				int32 CalcedDamage = FMath::Max(0, EffectInfo.Damage - BaseDeffence);
				LeftLifePoint -= CalcedDamage;

				MapManager->Consume(ApplyEffectInfo.ArrayLocation, ApplyEffectInfo.Index);
			}
		}
	}
}
