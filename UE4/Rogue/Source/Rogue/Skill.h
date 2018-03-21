// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Skill.generated.h"

namespace Skill
{
}

UENUM(BlueprintType)
enum class ESkill : uint8
{
	None,
};

USTRUCT(BlueprintType)
struct FSkillInfo
{
	GENERATED_USTRUCT_BODY()
	
	FSkillInfo(): bAcceptRotation(false), ConsumeSP()
	{}

public:
	bool				bAcceptRotation;
	int32				ConsumeSP;
	TArray<FVector2D>	AreaList;
};
