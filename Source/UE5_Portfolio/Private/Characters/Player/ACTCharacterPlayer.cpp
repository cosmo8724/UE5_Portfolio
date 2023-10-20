// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Player/ACTCharacterPlayer.h"

#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

AACTCharacterPlayer::AACTCharacterPlayer()
{
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->bUsePawnControlRotation = true;

	PlayerCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("PlayerCamera"));
	PlayerCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	PlayerCamera->bUsePawnControlRotation = false;
}

void AACTCharacterPlayer::BeginPlay()
{
	Super::BeginPlay();

	if (APlayerController* PlayerController{ Cast<APlayerController>(GetController()) }; PlayerController && DefaultMappingContext) {
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem{ ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer())}) {
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
}

void AACTCharacterPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent{ CastChecked<UEnhancedInputComponent>(PlayerInputComponent) }) {
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AACTCharacterPlayer::Move);
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AACTCharacterPlayer::Look);
		//EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &AACTCharacterPlayer::Jump);
	}
}

void AACTCharacterPlayer::Move(const FInputActionValue& InValue)
{
	const FInputActionValue::Axis2D Value{ InValue.Get<FInputActionValue::Axis2D>() };

	const FRotator ControlRotation{ GetControlRotation() };
	const FRotator YawRotation{ 0.f, ControlRotation.Yaw, 0.f };
	const FRotationMatrix YawMatrix{ YawRotation };

	const FVector Forward{ YawMatrix.GetUnitAxis(EAxis::X) };
	const FVector Right{ YawMatrix.GetUnitAxis(EAxis::Y) };

	AddMovementInput(Forward, Value.X);
	AddMovementInput(Right, Value.Y);
}

void AACTCharacterPlayer::Look(const FInputActionValue& InValue)
{
	const FInputActionValue::Axis2D Value{ InValue.Get<FInputActionValue::Axis2D>() };

	AddControllerYawInput(Value.X);
	AddControllerPitchInput(Value.Y);
}
