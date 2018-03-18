// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerBase.h"
#include "RogueUtility.h"
#include "MapManager.h"
#include "RogueMainInputComponent.h"

APlayerBase::APlayerBase(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
	, bCanAction(false)
{
	ObjectInitializer.CreateDefaultSubobject<URogueMainInputComponent>(this, "RogueMainInputComponent");
}

void APlayerBase::ApplyDamage()
{
	if (MapManager)
	{
		FApplyEffectList ApplyEffectList;
		MapManager->Search(EEffectType::Eff_EnemyAttack, ApplyEffectList);

		for (FApplyEffectInfo ApplyEffectInfo : ApplyEffectList)
		{
			if (ArrayLocation == ApplyEffectInfo.ArrayLocation)
			{
				const FEffectInfo EffectInfo = MapManager->GetEffectInfo(ApplyEffectInfo.ArrayLocation, ApplyEffectInfo.Index);
				LeftLifePoint -= EffectInfo.Damage;

				MapManager->Consume(ApplyEffectInfo.ArrayLocation, ApplyEffectInfo.Index);
			}
		}
	}
}

bool APlayerBase::TryMove(EDirection_Type DirType)
{
	FVector2D Diretion = RogueUtility::GetDirection(DirType);
	const FVector2D NextLocation = ArrayLocation + Diretion;

	if (MapManager->IsPossibleMove(NextLocation))
	{
		this->AdjustLocation(NextLocation);

		return true;
	}

	return false;
}
