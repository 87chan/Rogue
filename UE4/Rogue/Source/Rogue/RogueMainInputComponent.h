// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/InputComponent.h"
#include "RogueMainInputComponent.generated.h"

/**
 * 
 */
UCLASS()
class ROGUE_API URogueMainInputComponent : public UInputComponent
{
	GENERATED_BODY()
	
public:
	//~ ActorComponent interface.
	void BeginPlay() override;
	
	UFUNCTION()
	void Test();
};
