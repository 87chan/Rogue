// Fill out your copyright notice in the Description page of Project Settings.

#include "EnemyBase.h"
#include "Rogue.h"
#include "RogueUtility.h"
#include "MapManager.h"

AEnemyBase::AEnemyBase(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
	, EnemyManager(nullptr)
	, ActivePhase(EPhaseType::None)
	, bConsumeAction(false)
{
}

void AEnemyBase::BeginPlay()
{
	Super::BeginPlay();
}

void AEnemyBase::TurnToPlayer()
{
	FVector2D TargetArrayLocation = MapManager->Search(EFieldType::Player);
	FVector2D TargetDirection = FVector2D(TargetArrayLocation - ArrayLocation).ClampAxes(-1.0f, 1.0f);
	EDirection_Type NextDirection = RogueUtility::GetDirection(TargetDirection);

	this->Turn(NextDirection);
}

void AEnemyBase::Move()
{
	if (MapManager)
	{
		FVector2D TargetArrayLocation = MapManager->Search(EFieldType::Player);
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
