// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/ACTAnimInstance.h"

#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "KismetAnimationLibrary.h"

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
		Velocity = CharacterMovement->Velocity;
		GroundSpeed = Velocity.Size2D();
		bIsIdle = GroundSpeed < MovingThreshould;
		Rotation = Owner->GetActorRotation();
		AimRotation = Owner->GetBaseAimRotation();
		Direction = UKismetAnimationLibrary::CalculateDirection(Velocity, Rotation);
	}
}
