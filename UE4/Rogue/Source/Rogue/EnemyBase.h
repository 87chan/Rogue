// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "RoguePawn.h"
#include "EnemyBase.generated.h"

class AEnemyManager;

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class ROGUE_API AEnemyBase : public ARoguePawn
{
	GENERATED_BODY()
	
public:
	AEnemyBase(const FObjectInitializer& ObjectInitializer);

public:
	UFUNCTION(BlueprintCallable, Category = "Rogue|EnemyBase")
	const EDirection_Type Move();

public:
	UPROPERTY(BlueprintReadWrite, Category = "Rogue|EnemyBase")
	AEnemyManager* EnemyManager;

	UPROPERTY(BlueprintReadWrite, Category = "Rogue|EnemyBase")
	EPhaseType ActivePhase;
};
