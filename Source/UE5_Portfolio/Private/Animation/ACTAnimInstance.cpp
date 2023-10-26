// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/ACTAnimInstance.h"

#include "GameFramework/Character.h"

UACTAnimInstance::UACTAnimInstance()
{
}

void UACTAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	Owner = Cast<ACharacter>(GetOwningActor());
	if (Owner) {
		CharacterMovement = Owner->GetCharacterMovement();
	}
}

void UACTAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (CharacterMovement) {
		
	}
}
