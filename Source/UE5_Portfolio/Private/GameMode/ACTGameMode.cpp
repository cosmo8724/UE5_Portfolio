// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMode/ACTGameMode.h"
#include "Characters/Player/ACTCharacterPlayer.h"
#include "Characters/Player/ACTPlayerController.h"

AACTGameMode::AACTGameMode()
{
	DefaultPawnClass = AACTCharacterPlayer::StaticClass();
	PlayerControllerClass = AACTPlayerController::StaticClass();
}
