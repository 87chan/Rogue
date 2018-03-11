// Fill out your copyright notice in the Description page of Project Settings.

#include "EnemyManager.h"
#include "Rogue.h"
#include "EnemyBase.h"
#include "RogueGameModeBase.h"
#include "Engine/World.h"

AEnemyManager::AEnemyManager(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
	, DefaultEnemyNum(0)
	, ActivePhase(EPhaseType::Phase_None)
{
	PrimaryActorTick.bCanEverTick = true;
}

void AEnemyManager::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (ActivePhase != EPhaseType::Phase_None)
	{
		for (const AEnemyBase* Enemy : EnemyArray)
		{
			if (Enemy->ActivePhase == ActivePhase)
			{
				return;
			}
		}

		if (ARogueGameModeBase* GameMode = Cast<ARogueGameModeBase>(this->GetWorld()->GetAuthGameMode()))
		{
			this->ActivePhase = EPhaseType::Phase_None;

			GameMode->NextPhase();
		}
	}
}

void AEnemyManager::RegisterEnemy(AEnemyBase* Enemy)
{
	EnemyArray.Add(Enemy);
}
