// Fill out your copyright notice in the Description page of Project Settings.

#include "MapManager.h"

AMapManager::AMapManager(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
	, Unit(100)
	, Width(10)
	, Height(10)
{
}

FVector AMapManager::GetOffset() const
{
	return FVector(Unit * Width * -0.5f, Unit * Height * 0.5f, 0.0f) - FVector(Unit * -0.5f, Unit * 0.5f, 0.0f);
}
