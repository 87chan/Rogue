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

	virtual EEffectType GetAttackType() const { return EEffectType::Eff_None; }

public:
	UFUNCTION(BlueprintPure, Category = "Rogue|RoguePawn")
	bool CheckAdjacent(EFieldType Type);

	UFUNCTION(BlueprintCallable, Category = "Rogue|RoguePawn")
	void Turn(EDirection_Type DirType);
	
	UFUNCTION(BlueprintCallable,Category = "Rogue|RoguePawn")
	void AdjustLocation(FVector2D InArrayLocation);

	UFUNCTION(BlueprintCallable, Category = "Rogue|RoguePawn")
	void Attack();

	UFUNCTION(BlueprintCallable, Category = "Rogue|RoguePawn")
	virtual void ApplyDamage() {}

public:
	UPROPERTY(BlueprintReadWrite, Category = "Rogue|RoguePawn")
	AMapManager* MapManager;

	UPROPERTY(BlueprintReadWrite, Category = "Rogue|RoguePawn")
	FVector2D ArrayLocation;

	UPROPERTY(BlueprintReadWrite, Category = "Rogue|RoguePawn")
	EDirection_Type Direction;

	UPROPERTY(BlueprintReadWrite, Category = "Rogue|RoguePawn")
	int32 MaxLifePoint;

	UPROPERTY(BlueprintReadWrite, Category = "Rogue|RoguePawn")
	int32 LeftLifePoint;

	UPROPERTY(BlueprintReadWrite, Category = "Rogue|RoguePawn")
	int32 RiskPoint;

	UPROPERTY(BlueprintReadWrite, Category = "Rogue|RoguePawn")
	int32 BaseAttack;

	UPROPERTY(BlueprintReadWrite, Category = "Rogue|RoguePawn")
	int32 BaseDeffence;
};
