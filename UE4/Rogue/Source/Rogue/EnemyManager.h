// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <GameFramework/Actor.h>
#include "Rogue.h"
#include "EnemyManager.generated.h"

class AEnemyBase;

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class ROGUE_API AEnemyManager : public AActor
{
	GENERATED_BODY()
	
	AEnemyManager(const FObjectInitializer& ObjectInitializer);

	//~ ActorInterface.
	void Tick(float DeltaSeconds);

public:
	UFUNCTION(BlueprintCallable,Category = "EnemyManager")
	void RegisterEnemy(AEnemyBase* Enemy);

	UFUNCTION(BlueprintCallable, Category = "EnemyManager")
	void NotifyActivePhase(EPhaseType Type);

public:
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Rogue|EnemyManager")
	int32	DefaultEnemyNum;

	UPROPERTY(BlueprintReadWrite, Category = "Rogue|EnemyManager")
	EPhaseType	ActivePhase;

private:
	TArray<AEnemyBase*> EnemyArray;
};
