// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Rogue.h"

class AActor;
class ARogueGameModeBase;

namespace RogueUtility
{
	FRotator GetRotation(EDirection_Type DirType);
	FVector2D GetDirection(EDirection_Type DirType);
}
