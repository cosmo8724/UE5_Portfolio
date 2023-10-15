// Copyright Epic Games, Inc. All Rights Reserved.

#include "UE5_PortfolioGameMode.h"
#include "UE5_PortfolioCharacter.h"
#include "UObject/ConstructorHelpers.h"

AUE5_PortfolioGameMode::AUE5_PortfolioGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
