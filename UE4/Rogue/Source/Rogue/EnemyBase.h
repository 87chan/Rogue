// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "RoguePawn.h"
#include "EnemyBase.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class ROGUE_API AEnemyBase : public ARoguePawn
{
	GENERATED_BODY()
	
public:
	AEnemyBase(const FObjectInitializer& ObjectInitializer);
};
