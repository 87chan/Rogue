// Fill out your copyright notice in the Description page of Project Settings.

#include "MapManager.h"
#include "Rogue.h"

AMapManager::AMapManager(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
	, Width(10)
	, Height(10)
{
}

FVector AMapManager::GetOffset() const
{
	FVector Offset = FVector::ZeroVector;

	if (Width % 2 == 0)
	{
		Offset.Y += Rogue::Unit * Width * 0.5f;
		Offset.Y -= Rogue::Unit * 0.5f;
	}
	else if (Width != 1)
	{
		Offset.Y += Rogue::Unit * (Width - 1) * 0.5f;
	}

	if (Height % 2 == 0)
	{
		Offset.X -= Rogue::Unit * Height * 0.5f;
		Offset.X += Rogue::Unit * 0.5f;
	}
	else if (Height != 1)
	{
		Offset.X -= Rogue::Unit * (Height - 1) * 0.5f;
	}

	return Offset;
}

FVector AMapManager::GetRandomArrayLocation() const
{
	int32 X = FMath::Rand() % Width;
	int32 Y = FMath::Rand() % Height;

	// Check Floor.

	return FVector((float)X, (float)Y, 0.0f);
}

bool AMapManager::IsPossibleMove(FVector ArrayLocation) const
{
	// Compare to list.
	// NotFloor or OutRange, return false.

	return true;
}
