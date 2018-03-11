// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "RogueUtility.h"
#include "CoreMinimal.h"
#include "Rogue.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"
#include "RogueGameModeBase.h"

namespace RogueUtility
{
	FRotator GetRotation(EDirection_Type DirType)
	{
		return FRotator(0.0f, (int32)DirType * Rogue::Direction_Degree_Interval, 0.0f);
	}

	FVector2D GetDirection(EDirection_Type DirType)
	{
		FVector2D Direction = FVector2D::ZeroVector;

		Direction.X += (float)(
			DirType == EDirection_Type::Dir_UpperRight ||
			DirType == EDirection_Type::Dir_Right ||
			DirType == EDirection_Type::Dir_LowerRight);

		Direction.X -= (float)(
			DirType == EDirection_Type::Dir_UpperLeft ||
			DirType == EDirection_Type::Dir_Left ||
			DirType == EDirection_Type::Dir_LowerLeft);

		Direction.Y += (float)(
			DirType == EDirection_Type::Dir_Lower ||
			DirType == EDirection_Type::Dir_LowerRight ||
			DirType == EDirection_Type::Dir_LowerLeft);

		Direction.Y -= (float)(
			DirType == EDirection_Type::Dir_Upper ||
			DirType == EDirection_Type::Dir_UpperRight ||
			DirType == EDirection_Type::Dir_UpperLeft);

		return Direction;
	}
}
