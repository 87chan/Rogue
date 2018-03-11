// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Rogue.h"
#include "RogueGameModeBase.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FPhaseChangedDelegate, EPhaseType, PrevPhase, EPhaseType, NextPhase);

/**
 * 
 */
UCLASS()
class ROGUE_API ARogueGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	ARogueGameModeBase(const FObjectInitializer& ObjectInitializer);

public:
	UFUNCTION(BlueprintPure, Category = "Rogue|RogueGameModeBase")
	bool CheckCurrentPhase(EPhaseType Type) const { return (CurrentPhase == Type); }

	UFUNCTION(BlueprintCallable, Category = "Rogue|RogueGameModeBase")
	void BeginPhase(EPhaseType NextPhase);

	UFUNCTION(BlueprintCallable, Category = "Rogue|RogueGameModeBase")
	void NextPhase();

public:
	UPROPERTY(BlueprintAssignable, Category = "Rogue|RogueGameModeBase")
	FPhaseChangedDelegate OnPhaseChanged;

private:
	EPhaseType CurrentPhase;
};
