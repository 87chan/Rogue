// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Rogue.h"

class AActor;
class ARogueGameModeBase;

namespace RogueUtility
{
	const FRotator GetRotation(EDirection_Type DirType);
	const FVector2D GetDirection(EDirection_Type DirType);
	EDirection_Type GetDirection(const FVector2D& Direction);
	EDirection_Type GetRandomDirection();
}
