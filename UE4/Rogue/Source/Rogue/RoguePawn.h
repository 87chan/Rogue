// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <GameFramework/Pawn.h>
#include "Rogue.h"
#include "RoguePawn.generated.h"

class AMapManager;
class USceneComponent;

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class ROGUE_API ARoguePawn : public APawn
{
	GENERATED_BODY()
	
public:
	ARoguePawn(const FObjectInitializer& ObjectInitializer);

	//~Actor interface.
	void BeginPlay() override;

public:
	virtual EFieldType GetFieldType() const { return EFieldType::Fld_None; }

public:
	UFUNCTION(BlueprintCallable, Category = "Rogue|RoguePawn")
	void Turn(EDirection_Type DirType);
	
	UFUNCTION(BlueprintCallable,Category = "Rogue|RoguePawn")
	void AdjustLocation(FVector2D InArrayLocation);

public:
	UPROPERTY(BlueprintReadWrite, Category = "Rogue|RoguePawn")
	AMapManager* MapManager;

	UPROPERTY(BlueprintReadWrite, Category = "Rogue|RoguePawn")
	FVector2D ArrayLocation;

	UPROPERTY(BlueprintReadWrite, Category = "Rogue|RoguePawn")
	EDirection_Type Direction;
};
