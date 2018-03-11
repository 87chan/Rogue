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

const EDirection_Type AEnemyBase::Move()
{
	EDirection_Type NextDirection = static_cast<EDirection_Type>(FMath::Rand() % (int32)EDirection_Type::Dir_Num);
	FVector2D NextArrayLocation = ArrayLocation + RogueUtility::GetDirection(NextDirection);

	if (MapManager->IsPossibleMove(NextArrayLocation))
	{
		MapManager->ChangeFieldType(ArrayLocation, NextArrayLocation, EFieldType::Fld_Enemy);
		this->AdjustLocation(NextArrayLocation);

		return NextDirection;
	}

	return Direction;
}
