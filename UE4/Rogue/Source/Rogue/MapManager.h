// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <GameFramework/Actor.h>
#include "MapManager.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class ROGUE_API AMapManager : public AActor
{
	GENERATED_BODY()
	
	AMapManager(const FObjectInitializer& ObjectInitializer);
	
public:
	UFUNCTION(BlueprintCallable, Category = "MapManager")
	FVector GetOffset() const;

	UFUNCTION(BlueprintCallable, Category = "MapManager")
	FVector GetRandomArrayLocation() const;

	UFUNCTION(BlueprintCallable, Category = "MapManager")
	bool IsPossibleMove(FVector ArrayLocation) const;

public:
	
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "MapManager")
	int32	Width;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "MapManager")
	int32	Height;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "MapManager")
	bool	bRandomGenerate;
};
