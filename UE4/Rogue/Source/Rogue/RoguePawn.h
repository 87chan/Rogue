// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <GameFramework/Pawn.h>
#include "RoguePawn.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class ROGUE_API ARoguePawn : public APawn
{
	GENERATED_BODY()
	
public:
	ARoguePawn(const FObjectInitializer& ObjectInitializer);

public:
	UPROPERTY(BlueprintReadWrite, Category = "Rogue|RoguePawn")
	FVector ArrayLocation;
};
