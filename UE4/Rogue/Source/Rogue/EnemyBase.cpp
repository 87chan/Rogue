// Fill out your copyright notice in the Description page of Project Settings.

#include "EnemyBase.h"
#include "Rogue.h"
#include "RogueUtility.h"
#include "MapManager.h"

AEnemyBase::AEnemyBase(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
	, EnemyManager(nullptr)
	, ActivePhase(EPhaseType::Phase_None)
	, bConsumeAction(false)
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
		FApplyEffectList ApplyEffectList;
		MapManager->Search(EEffectType::Eff_PlayerAttack, ApplyEffectList);

		for (FApplyEffectInfo ApplyEffectInfo : ApplyEffectList)
		{
			if (ArrayLocation == ApplyEffectInfo.ArrayLocation)
			{
				const FEffectInfo EffectInfo = MapManager->GetEffectInfo(ApplyEffectInfo.ArrayLocation, ApplyEffectInfo.Index);
				LeftLifePoint -= EffectInfo.Damage;

				MapManager->Consume(ApplyEffectInfo.ArrayLocation, ApplyEffectInfo.Index);
			}
		}
	}
}

void AEnemyBase::TurnToPlayer()
{
	FVector2D TargetArrayLocation = MapManager->Search(EFieldType::Fld_Player);
	FVector2D TargetDirection = FVector2D(TargetArrayLocation - ArrayLocation).ClampAxes(-1.0f, 1.0f);
	EDirection_Type NextDirection = RogueUtility::GetDirection(TargetDirection);

	this->Turn(NextDirection);
}

void AEnemyBase::Move()
{
	if (MapManager)
	{
		FVector2D TargetArrayLocation = MapManager->Search(EFieldType::Fld_Player);
		FVector2D TargetDirection = FVector2D(TargetArrayLocation - ArrayLocation).ClampAxes(-1.0f, 1.0f);
		FVector2D NextArrayLocation = ArrayLocation + TargetDirection;

		if (MapManager->IsPossibleMove(NextArrayLocation))
		{
			this->AdjustLocation(NextArrayLocation);
		}

		this->TurnToPlayer();

		bConsumeAction = true;
	}
}
