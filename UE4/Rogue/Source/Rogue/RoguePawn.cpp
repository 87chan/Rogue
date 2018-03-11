// Fill out your copyright notice in the Description page of Project Settings.

#include "RoguePawn.h"
#include "Rogue.h"
#include "Components/StaticMeshComponent.h"

ARoguePawn::ARoguePawn(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
	, MapManagerRef(nullptr)
	, ArrayLocation(FVector2D::ZeroVector)
	, Direction(EDirection_Type::Dir_Lower)
{
}

void ARoguePawn::BeginPlay()
{
	Super::BeginPlay();
}

void ARoguePawn::Turn(UStaticMeshComponent* Mesh, EDirection_Type DirType)
{
	FRotator Rotation = FRotator(0.0f, (int32)DirType * Rogue::Direction_Degree_Interval, 0.0f);

	Mesh->SetRelativeRotation(Rotation);
}

void ARoguePawn::AdjustLocation(FVector2D ArrayLocation)
{
	FVector2D Location = FVector2D::ZeroVector;
	Location.X = -ArrayLocation.Y * Rogue::Unit;
	Location.Y = ArrayLocation.X * Rogue::Unit;

	this->SetActorLocation(FVector(Location.X, Location.Y, 0.0f));
}
