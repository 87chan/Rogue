// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <GameFramework/Actor.h>
#include "Rogue.h"
#include "MapManager.generated.h"

class AEnemyManager;

USTRUCT(BlueprintType)
struct FEffectInfo
{
	GENERATED_USTRUCT_BODY()

	FEffectInfo() : EffectType(EEffectType::Eff_None), Damage() {}
	FEffectInfo(EEffectType InEffectType, int32 InDamage) : EffectType(InEffectType), Damage(InDamage) {}

public:
	EEffectType	EffectType;
	int32		Damage;
};

USTRUCT(BlueprintType)
struct FFieldInfo
{
	GENERATED_USTRUCT_BODY()

	FFieldInfo() : bOpen(false), FieldType(EFieldType::Fld_None) {}
	FFieldInfo(EFieldType InFieldType, EEffectType InEffectType) : bOpen(false), FieldType(InFieldType) {}

public:
	bool		bOpen;
	EFieldType	FieldType;
	TArray<FEffectInfo>	EffectList;
};

struct FApplyEffectInfo
{
	FApplyEffectInfo() :ArrayLocation(FVector2D::ZeroVector), Index() {}

public:
	FVector2D	ArrayLocation;
	int32		Index;
};
typedef TArray<FApplyEffectInfo> FApplyEffectList;

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
	bool IsPossibleMove(const FVector2D& ArrayLocation) const;

public:
	const FEffectInfo GetEffectInfo(const FVector2D& InArrayLocation, int32 Index) const;
	void Consume(const FVector2D& InArrayLocation, int32 Index);

	bool CheckExist(const FVector2D& InArrayLocation, EFieldType Type);
	bool CheckAdjacent(const FVector2D& InArrayLocation, EFieldType Type);

	void ChangeFieldType(const FVector2D& PrevArrayLoc, const FVector2D& NextArrayLoc, EFieldType Type);

	void EffectInfoSet(const FVector2D& ArrayLocation, FEffectInfo Info);

	const FVector2D Search(EFieldType Type) const;
	void Search(EEffectType Type, FApplyEffectList& OutList) const;

private:
	AActor* SpawnActor(UClass* Class, const FVector2D& ArrayLocation, EFieldType Type);

	void FieldTypeSet(const FVector2D& ArrayLocation, EFieldType Type);

public:
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Rogue|MapManager")
	int32	Width;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Rogue|MapManager")
	int32	Height;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Rogue|MapManager")
	bool	bRandomGenerate;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Rogue|MapManager")
	int32	DefaultEnemyNum;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Rogue|MapManager")
	UClass* WallClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Rogue|MapManager")
	UClass* GoalClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Rogue|MapManager")
	UClass* EnemyClass;

	UPROPERTY(BlueprintReadWrite, Category = "Rogue|MapManager")
	AEnemyManager* EnemyManager;

private:
	bool bCreatedMap;

private:
	TArray<TArray<FFieldInfo>> FieldArray;
};
