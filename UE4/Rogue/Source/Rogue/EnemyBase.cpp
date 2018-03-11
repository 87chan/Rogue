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

	Direction = RogueUtility::GetRandomDirection();
}

const EDirection_Type AEnemyBase::Move()
{
	FVector2D TargetArrayLocation = MapManager->Search(EFieldType::Fld_Player);
	FVector2D Direction = FVector2D(TargetArrayLocation - ArrayLocation).ClampAxes(-1.0f, 1.0f);
	EDirection_Type NextDirection = RogueUtility::GetDirection(Direction);
	FVector2D NextArrayLocation = ArrayLocation + Direction;

	if (MapManager->IsPossibleMove(NextArrayLocation))
	{
		MapManager->ChangeFieldType(ArrayLocation, NextArrayLocation, EFieldType::Fld_Enemy);
		this->AdjustLocation(NextArrayLocation);
	}

	return NextDirection;
}
