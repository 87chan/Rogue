// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

namespace Rogue
{
	const int32 Unit = 100;
	const int32 Direction_Degree_Interval = 45;
}

UENUM(BlueprintType, meta = (Bitflags))
enum class EFieldType : uint8
{
	None		= 0x00,
	Room		= 0x01,
	Way			= 0x02,
	Wall		= 0x04,
	Goal		= 0x08,
	Player		= 0x10,
	Enemy		= 0x20,
	Trap		= 0x40,

	Grp_BottomLayer			=	Room | Way,

	Grp_MiddleLayer			=	Goal | Trap,

	Grp_PlacementableTop	=	Grp_BottomLayer | Grp_MiddleLayer,

	Grp_TopLayer			=	Wall | Player | Enemy,
};
ENUM_CLASS_FLAGS(EFieldType)

UENUM(BlueprintType, meta = (Bitflags))
enum class EEffectType : uint8
{
	None			= 0x00,
	PlayerAttack	= 0x01,
	EnemyAttack		= 0x02,
	Trap			= 0x04,
};
ENUM_CLASS_FLAGS(EEffectType)

UENUM(BlueprintType)
enum class EPhaseType : uint8
{
	PlayerAction,
	PlayerAttack,
	EnemyMove,
	TrapAction,
	EnemyAction,
	EnemyAttack,
	StairCheck,

	Num			UMETA(Hidden),
	None,
};

UENUM(BlueprintType)
enum class EDirection_Type : uint8
{
	Upper,
	UpperRight,
	Right,
	LowerRight,
	Lower,
	LowerLeft,
	Left,
	UpperLeft,

	Num				UMETA(Hidden),
	None,
};
