// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <GameFramework/Pawn.h>
#include "RoguePawn.generated.h"

class AMapManager;

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class ROGUE_API ARoguePawn : public APawn
{
	GENERATED_BODY()
	
public:
	ARoguePawn(const FObjectInitializer& ObjectInitializer);

	UFUNCTION(BlueprintCallable,Category = "Rogue|RoguePawn")
	void AdjustLocation(FVector2D ArrayLocation);

public:
	UPROPERTY(BlueprintReadWrite, Category = "Rogue|RoguePawn")
	AMapManager* MapManagerRef;

	UPROPERTY(BlueprintReadWrite, Category = "Rogue|RoguePawn")
	FVector2D ArrayLocation;	
};
