// Fill out your copyright notice in the Description page of Project Settings.

#include "RoguePawn.h"
#include "Rogue.h"
#include "Components/StaticMeshComponent.h"
#include "RogueUtility.h"
#include "MapManager.h"

ARoguePawn::ARoguePawn(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
	, MapManager(nullptr)
	, ArrayLocation(FVector2D::ZeroVector)
	, Direction(EDirection_Type::Dir_None)
	, MaxLifePoint()
	, LeftLifePoint()
	, RiskPoint()
	, BaseAttack()
	, BaseDeffence()
{
}

void ARoguePawn::BeginPlay()
{
	Super::BeginPlay();

	Direction = RogueUtility::GetRandomDirection();
	this->Turn(Direction);
}

void ARoguePawn::Turn(EDirection_Type DirType)
{
	RootComponent->SetRelativeRotation(RogueUtility::GetRotation(DirType));
}

void ARoguePawn::AdjustLocation(FVector2D InArrayLocation)
{
	MapManager->ChangeFieldType(ArrayLocation, InArrayLocation, this->GetFieldType());

	ArrayLocation = InArrayLocation;

	FVector2D Location = FVector2D::ZeroVector;
	Location.X = -ArrayLocation.Y * Rogue::Unit;
	Location.Y = ArrayLocation.X * Rogue::Unit;

	this->SetActorLocation(FVector(Location.X, Location.Y, 0.0f));
}

void ARoguePawn::Attack()
{
	FVector2D AttackArrayLocation = ArrayLocation + RogueUtility::GetDirection(Direction);
	MapManager->EffectTypeSet(AttackArrayLocation, this->GetAttackType());
}
