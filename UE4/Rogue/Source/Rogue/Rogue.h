// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

namespace Rogue
{
	const int32 Unit = 100;
}

UENUM(BlueprintType, meta = (Bitflags))
enum class EFieldType : uint8
{
	Fld_None = 0x00,
	Fld_Floor = 0x01,
	Fld_Wall = 0x02,
	Fld_Player = 0x04,
	Fld_Enemy = 0x08,
};
ENUM_CLASS_FLAGS(EFieldType)
