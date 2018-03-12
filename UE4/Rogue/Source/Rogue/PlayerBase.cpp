// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerBase.h"
#include "RogueUtility.h"
#include "MapManager.h"
#include "RogueMainInputComponent.h"

APlayerBase::APlayerBase(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
	, bCanAction(false)
{
	ObjectInitializer.CreateDefaultSubobject<URogueMainInputComponent>(this, "RogueMainInputComponent");
}

bool APlayerBase::TryMove(EDirection_Type DirType)
{
	FVector2D Diretion = RogueUtility::GetDirection(DirType);
	const FVector2D NextLocation = ArrayLocation + Diretion;

	if (MapManager->IsPossibleMove(NextLocation))
	{
		MapManager->ChangeFieldType(ArrayLocation, NextLocation, EFieldType::Fld_Player);
		this->AdjustLocation(NextLocation);

		return true;
	}

	return false;
}
