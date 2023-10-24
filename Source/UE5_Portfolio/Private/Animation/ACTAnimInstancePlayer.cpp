// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/ACTAnimInstancePlayer.h"

#include "Characters/Player/ACTCharacterPlayer.h"

UACTAnimInstancePlayer::UACTAnimInstancePlayer()
{
}

void UACTAnimInstancePlayer::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	if (Owner) {
		Player = Cast<AACTCharacterPlayer>(Owner);
	}
}

void UACTAnimInstancePlayer::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (Player) {
		bIsArmed = Player->IsArmed();
	}
}