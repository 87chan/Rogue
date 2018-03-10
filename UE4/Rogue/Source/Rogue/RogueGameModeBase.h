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
	UPROPERTY(BlueprintAssignable, Category = "Rogue|RogueGameModeBase")
	FPhaseChangedDelegate OnPhaseChanged;
};
