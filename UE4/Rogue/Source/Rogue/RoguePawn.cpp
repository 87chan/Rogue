// Fill out your copyright notice in the Description page of Project Settings.

#include "RoguePawn.h"
#include "Rogue.h"

ARoguePawn::ARoguePawn(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
	, MapManagerRef(nullptr)
	, ArrayLocation(FVector::ZeroVector)
{
}

void ARoguePawn::AdjustLocation(FVector ArrayLocation)
{
	FVector Location = FVector::ZeroVector;
	Location.X = -ArrayLocation.Y * Rogue::Unit;
	Location.Y = ArrayLocation.X * Rogue::Unit;

	this->SetActorLocation(Location);
}
