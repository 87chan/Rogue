// Fill out your copyright notice in the Description page of Project Settings.

#include "RogueMainInputComponent.h"
#include "GameFramework/PlayerInput.h"

void URogueMainInputComponent::BeginPlay()
{
	UPlayerInput::AddEngineDefinedActionMapping(FInputActionKeyMapping(TEXT("Test"), EKeys::T));

	this->BindAction(TEXT("Test"), IE_Pressed, this, &URogueMainInputComponent::Test);
}

void URogueMainInputComponent::Test()
{
	UE_LOG(LogTemp, Log, TEXT("Hello"));
}
