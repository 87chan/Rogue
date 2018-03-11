// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "RoguePawn.h"
#include "PlayerBase.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class ROGUE_API APlayerBase : public ARoguePawn
{
	GENERATED_BODY()
	
public:
	APlayerBase(const FObjectInitializer& ObjectInitializer);

public:
	UPROPERTY(BlueprintReadWrite,Category = "Rogue|PlayerBase")
	bool bCanAction;
};
