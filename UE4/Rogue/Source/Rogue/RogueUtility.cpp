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
	const FRotator GetRotation(EDirection_Type DirType)
	{
		return FRotator(0.0f, (int32)DirType * Rogue::Direction_Degree_Interval, 0.0f);
	}

	const FVector2D GetDirection(EDirection_Type DirType)
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

	EDirection_Type GetDirection(const FVector2D& Direction)
	{
		TMap<EDirection_Type, FVector2D>DirectionMap;
		DirectionMap.Add(EDirection_Type::Dir_Upper, FVector2D(0.0f, -1.0f));
		DirectionMap.Add(EDirection_Type::Dir_UpperRight, FVector2D(1.0f, -1.0f));
		DirectionMap.Add(EDirection_Type::Dir_Right, FVector2D(1.0f, 0.0f));
		DirectionMap.Add(EDirection_Type::Dir_LowerRight, FVector2D(1.0f, 1.0f));
		DirectionMap.Add(EDirection_Type::Dir_Lower, FVector2D(0.0f, 1.0f));
		DirectionMap.Add(EDirection_Type::Dir_LowerLeft, FVector2D(-1.0f, 1.0f));
		DirectionMap.Add(EDirection_Type::Dir_Left, FVector2D(-1.0f, 0.0f));
		DirectionMap.Add(EDirection_Type::Dir_UpperLeft, FVector2D(-1.0f, -1.0f));

		for (auto It = DirectionMap.CreateConstIterator(); It; ++It)
		{
			if ((*It).Value == Direction)
			{
				return (*It).Key;
			}
		}

		return EDirection_Type::Dir_None;
	}

	EDirection_Type GetRandomDirection()
	{
		return static_cast<EDirection_Type>(FMath::Rand() % (int32)EDirection_Type::Dir_Num);
	}
}
