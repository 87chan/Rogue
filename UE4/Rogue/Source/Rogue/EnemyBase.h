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

	//~ Actor interface.
	void BeginPlay();

	//~ ARoguePawn interface.
	EFieldType GetFieldType() const override { return EFieldType::Enemy; }

	EEffectType GetAttackType() const override { return EEffectType::EnemyAttack; }

public:
	UFUNCTION(BlueprintCallable, Category = "Rogue|EnemyBase")
	void TurnToPlayer();

	UFUNCTION(BlueprintCallable, Category = "Rogue|EnemyBase")
	void Move();

public:
	UPROPERTY(BlueprintReadWrite, Category = "Rogue|EnemyBase")
	AEnemyManager* EnemyManager;

	UPROPERTY(BlueprintReadWrite, Category = "Rogue|EnemyBase")
	EPhaseType ActivePhase;

	UPROPERTY(BlueprintReadWrite, Category = "Rogue|EnemyBase")
	bool bConsumeAction;
};
