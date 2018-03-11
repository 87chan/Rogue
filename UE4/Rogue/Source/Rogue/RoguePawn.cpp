// Fill out your copyright notice in the Description page of Project Settings.

#include "RoguePawn.h"
#include "Rogue.h"
#include "Components/StaticMeshComponent.h"
#include "RogueUtility.h"
#include "MapManager.h"

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
	Mesh->SetRelativeRotation(RogueUtility::GetRotation(DirType));
}

bool ARoguePawn::TryMove(EDirection_Type DirType)
{
	FVector2D Diretion = RogueUtility::GetDirection(DirType);

	if (MapManagerRef->IsPossibleMove(ArrayLocation + Diretion))
	{
		ArrayLocation += Diretion;
		this->AdjustLocation(ArrayLocation);

		return true;
	}

	return false;
}

void ARoguePawn::AdjustLocation(FVector2D ArrayLocation)
{
	FVector2D Location = FVector2D::ZeroVector;
	Location.X = -ArrayLocation.Y * Rogue::Unit;
	Location.Y = ArrayLocation.X * Rogue::Unit;

	this->SetActorLocation(FVector(Location.X, Location.Y, 0.0f));
}
