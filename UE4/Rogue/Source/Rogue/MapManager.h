// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <GameFramework/Actor.h>
#include "Rogue.h"
#include "MapManager.generated.h"

USTRUCT(BlueprintType)
struct FFieldInfo
{
	GENERATED_USTRUCT_BODY()

	FFieldInfo() : bOpen(false), Type(EFieldType::Fld_None) {}
	FFieldInfo(EFieldType InType) : bOpen(false), Type(InType) {}

public:
	bool		bOpen;
	EFieldType	Type;
};

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class ROGUE_API AMapManager : public AActor
{
	GENERATED_BODY()
	
	AMapManager(const FObjectInitializer& ObjectInitializer);
	
public:
	UFUNCTION(BlueprintCallable, Category = "Rogue|MapManager")
	void CreateMap();

	UFUNCTION(BlueprintCallable, Category = "Rogue|MapManager")
	FVector2D GetOffset() const;

	UFUNCTION(BlueprintCallable, Category = "Rogue|MapManager")
	FVector2D GetRandomArrayLocation() const;

	UFUNCTION(BlueprintCallable, Category = "Rogue|MapManager")
	bool IsPossibleMove(FVector2D ArrayLocation) const;

private:
	AActor* SpawnActor(UClass* Class, FVector2D ArrayLocation);

public:
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Rogue|MapManager")
	int32	Width;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Rogue|MapManager")
	int32	Height;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Rogue|MapManager")
	bool	bRandomGenerate;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Rogue|MapManager")
	UClass* WallClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Rogue|MapManager")
	UClass* GoalClass;

private:
	bool bCreatedMap;

private:
	TArray<TArray<FFieldInfo>> FieldArray;
};
