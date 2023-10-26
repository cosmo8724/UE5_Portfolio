// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Player/ACTCharacterPlayer.h"

#include "Weapons/ACTWeaponBase.h"
#include "Animation/ACTAnimInstancePlayer.h"

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

	if (MainWeaponClass) {
		MainWeapon = GetWorld()->SpawnActor<AACTWeaponBase>(MainWeaponClass);
		MainWeapon->AttachToComponent(GetMesh(), FAttachmentTransformRules{ EAttachmentRule::SnapToTarget, true }, TEXT("KatanaSheathHandle"));
	}
	if (SubWeaponClass) {
		SubWeapon = GetWorld()->SpawnActor<AACTWeaponBase>(SubWeaponClass);
		SubWeapon->AttachToComponent(GetMesh(), FAttachmentTransformRules{ EAttachmentRule::SnapToTarget, true }, TEXT("KatanaSheath"));
	}
}

void AACTCharacterPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent{ CastChecked<UEnhancedInputComponent>(PlayerInputComponent) }) {
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AACTCharacterPlayer::Move);
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Completed, this, &AACTCharacterPlayer::ResetMove);
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AACTCharacterPlayer::Look);
		//EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &AACTCharacterPlayer::Jump);
		EnhancedInputComponent->BindAction(ArmedAction, ETriggerEvent::Triggered, this, &AACTCharacterPlayer::Armed);
		EnhancedInputComponent->BindAction(RunAction, ETriggerEvent::Triggered, this, &AACTCharacterPlayer::MovementStateToRun);
		EnhancedInputComponent->BindAction(RunAction, ETriggerEvent::Completed, this, &AACTCharacterPlayer::MovementStateToWalk);
	}
}

void AACTCharacterPlayer::Move(const FInputActionValue& InValue)
{
	const float TargetMovementScale{ StaticCast<float>(MovementState) + 1.f };
	CurrentMovementScale = FMath::Lerp(CurrentMovementScale, TargetMovementScale, 0.05f);
	const FInputActionValue::Axis2D Value{ InValue.Get<FInputActionValue::Axis2D>() * CurrentMovementScale };

	const FRotator ControlRotation{ GetControlRotation() };
	const FRotator YawRotation{ 0.f, ControlRotation.Yaw, 0.f };
	const FRotationMatrix YawMatrix{ YawRotation };

	const FVector Forward{ YawMatrix.GetUnitAxis(EAxis::X) };
	const FVector Right{ YawMatrix.GetUnitAxis(EAxis::Y) };

	AddMovementInput(Forward, Value.X);
	AddMovementInput(Right, Value.Y);

	if (UACTAnimInstancePlayer* AnimInstancePlayer{ Cast<UACTAnimInstancePlayer>(GetMesh()->GetAnimInstance()) }) {
		AnimInstancePlayer->ExecuteOnMoveInputValueChanged(Value.X, Value.Y);
	}
}

void AACTCharacterPlayer::ResetMove(const FInputActionValue& InValue)
{
	const FInputActionValue::Axis2D Value{ InValue.Get<FInputActionValue::Axis2D>() };
	CurrentMovementScale = 0.f;

	if (UACTAnimInstancePlayer * AnimInstancePlayer{ Cast<UACTAnimInstancePlayer>(GetMesh()->GetAnimInstance()) }) {
		AnimInstancePlayer->ExecuteOnMoveInputValueChanged(Value.X, Value.Y);
	}
}

void AACTCharacterPlayer::Look(const FInputActionValue& InValue)
{
	const FInputActionValue::Axis2D Value{ InValue.Get<FInputActionValue::Axis2D>() };

	AddControllerYawInput(Value.X);
	AddControllerPitchInput(Value.Y);
}

void AACTCharacterPlayer::Armed()
{
	PlayIdleSwapMontage();
}

void AACTCharacterPlayer::MovementStateToRun()
{
	MovementState = EMovementState::RUN;
}

void AACTCharacterPlayer::MovementStateToWalk()
{
	MovementState = EMovementState::WALK;
}

void AACTCharacterPlayer::PlayIdleSwapMontage()
{
	UAnimInstance* AnimInstance{ GetMesh()->GetAnimInstance() };
	AnimInstance->Montage_Play(IdleSwapMontage);
	
	FName SectionName{ IdleSwapMontage->GetSectionName(bIsArmed) };
	AnimInstance->Montage_JumpToSection(SectionName, IdleSwapMontage);
}

void AACTCharacterPlayer::IdleToCombatIdle()
{
	MainWeapon->AttachToComponent(GetMesh(), FAttachmentTransformRules{ EAttachmentRule::SnapToTarget, true }, TEXT("KatanaWeapon"));
	bIsArmed = true;
}

void AACTCharacterPlayer::CombatIdleToIdle()
{
	MainWeapon->AttachToComponent(GetMesh(), FAttachmentTransformRules{ EAttachmentRule::SnapToTarget, true }, TEXT("KatanaSheathHandle"));
	bIsArmed = false;
}
