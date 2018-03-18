// Fill out your copyright notice in the Description page of Project Settings.

#include "EnemyBase.h"
#include "Rogue.h"
#include "RogueUtility.h"
#include "MapManager.h"

AEnemyBase::AEnemyBase(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
	, EnemyManager(nullptr)
	, ActivePhase(EPhaseType::Phase_None)
{
}

void AEnemyBase::BeginPlay()
{
	Super::BeginPlay();
}

void AEnemyBase::ApplyDamage()
{
	if (MapManager)
	{
		FVector2D ArrayLoc = FVector2D::ZeroVector;
		int32 Index = 0;
		MapManager->Search(EEffectType::Eff_PlayerAttack, ArrayLoc, Index);

		if (ArrayLocation == ArrayLoc)
		{
			const FEffectInfo EffectInfo = MapManager->GetEffectInfo(ArrayLoc, Index);
			LeftLifePoint -= EffectInfo.Damage;

			MapManager->Consume(ArrayLoc, Index);
		}
	}
}

const EDirection_Type AEnemyBase::Move()
{
	EDirection_Type NextDirection = EDirection_Type::Dir_None;

	if (MapManager)
	{
		FVector2D TargetArrayLocation = MapManager->Search(EFieldType::Fld_Player);
		FVector2D TargetDirection = FVector2D(TargetArrayLocation - ArrayLocation).ClampAxes(-1.0f, 1.0f);
		FVector2D NextArrayLocation = ArrayLocation + TargetDirection;
		NextDirection = RogueUtility::GetDirection(TargetDirection);

		if (MapManager->IsPossibleMove(NextArrayLocation))
		{
			this->AdjustLocation(NextArrayLocation);
		}
	}

	return NextDirection;
}
