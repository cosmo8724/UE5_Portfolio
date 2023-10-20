// Fill out your copyright notice in the Description page of Project Settings.

#include "Characters/ACTCharacterBase.h"

#include "Components/CapsuleComponent.h"
#include "GameFrameWork/CharacterMovementComponent.h"

AACTCharacterBase::AACTCharacterBase()
{
	PrimaryActorTick.bCanEverTick = false;

	/* Pawn */
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;

	/* Capsule */
	GetCapsuleComponent()->SetCollisionProfileName(TEXT("Pawn"));

	/* CharacterMovement */
	GetCharacterMovement()->bOrientRotationToMovement = true;

	/* SkeletalMesh */
	GetMesh()->SetCollisionProfileName(TEXT("CharacterMesh"));
}

void AACTCharacterBase::BeginPlay()
{
	Super::BeginPlay();
}

void AACTCharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AACTCharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}