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
	Fld_None		= 0x00,
	Fld_Room		= 0x01,
	Fld_Way			= 0x02,
	Fld_Wall		= 0x04,
	Fld_Goal		= 0x08,
	Fld_Player		= 0x10,
	Fld_Enemy		= 0x20,
	Fld_Trap		= 0x40,

	FldGrp_BottomLayer		=	Fld_Room | Fld_Way,

	FldGrp_MiddleLayer		=	Fld_Goal | Fld_Trap,

	FldGrp_PlacementableTop	=	FldGrp_BottomLayer | FldGrp_MiddleLayer,

	FldGrp_TopLayer			=	Fld_Wall | Fld_Player | Fld_Enemy,
};
ENUM_CLASS_FLAGS(EFieldType)

UENUM(BlueprintType)
enum class EPhaseType : uint8
{
	Phase_PlayerAction,
	Phase_EnemyMove,
	Phase_TrapAction,
	Phase_EnemyAction,
	Phase_StairCheck,

	Phase_Num			UMETA(Hidden),
	Phase_None,
};

UENUM(BlueprintType)
enum class EDirection_Type : uint8
{
	Dir_Upper,
	Dir_UpperRight,
	Dir_Right,
	Dir_LowerRight,
	Dir_Lower,
	Dir_LowerLeft,
	Dir_Left,
	Dir_UpperLeft,

	Dir_Num				UMETA(Hidden),
};
