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
	EFieldType GetFieldType() const override { return EFieldType::Fld_Player; }

	EEffectType GetAttackType() const override { return EEffectType::Eff_PlayerAttack; }

public:
	UFUNCTION(BlueprintCallable, Category = "Rogue|PlayerBase")
	bool TryMove(EDirection_Type DirType);

public:
	UPROPERTY(BlueprintReadWrite,Category = "Rogue|PlayerBase")
	bool bCanAction;
};
