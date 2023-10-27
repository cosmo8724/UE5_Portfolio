// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Player/ACTPlayerController.h"

void AACTPlayerController::BeginPlay()
{
	Super::ReceiveBeginPlay();
	
	FInputModeGameOnly InputModeGameOnly;
	SetInputMode(InputModeGameOnly);
}
