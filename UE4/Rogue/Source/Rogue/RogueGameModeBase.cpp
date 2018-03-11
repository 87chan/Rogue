// Fill out your copyright notice in the Description page of Project Settings.

#include "RogueGameModeBase.h"

ARogueGameModeBase::ARogueGameModeBase(const FObjectInitializer& ObjectInitializer)
	: Super()
	, CurrentPhase(EPhaseType::Phase_None)
{
}

void ARogueGameModeBase::BeginPhase(EPhaseType NextPhase)
{
	CurrentPhase = NextPhase;

	OnPhaseChanged.Broadcast(CurrentPhase, NextPhase);
}

void ARogueGameModeBase::NextPhase()
{
	EPhaseType TempCurrentPhase = CurrentPhase;
	int32 NextPhase = (int32)CurrentPhase;
	++NextPhase;
	NextPhase %= (int)EPhaseType::Phase_Num;
	CurrentPhase = static_cast<EPhaseType>(NextPhase);

	OnPhaseChanged.Broadcast(TempCurrentPhase, CurrentPhase);
}
