// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/ACTAnimInstancePlayer.h"

#include "Characters/Player/ACTCharacterPlayer.h"

#include "GameFramework/CharacterMovementComponent.h"
#include "Animation/AnimNode_StateMachine.h"
#include "KismetAnimationLibrary.h"
#include "Kismet/KismetMathLibrary.h"

UACTAnimInstancePlayer::UACTAnimInstancePlayer()
{
}

void UACTAnimInstancePlayer::ExecuteOnMoveInputValueChanged(float NewInputX, float NewInputY)
{
	OnMoveInputValueChanged.ExecuteIfBound(NewInputX, NewInputY);
}

void UACTAnimInstancePlayer::SetTurnInPlace(double InTurnInPlaceAngle)
{
	bIsNeedTurnInPlace = true;
	TurnInPlaceAngle = StaticCast<float>(InTurnInPlaceAngle);
	CurrentYaw = Player->GetActorRotation().Yaw;
	TargetYaw = CurrentYaw + TurnInPlaceAngle;
}

void UACTAnimInstancePlayer::ExecuteTurnInPlace()
{
	bIsNeedTurnInPlace = false;

	double DeltaRotate{ UKismetMathLibrary::Ease(CurrentYaw, TargetYaw, GetCurveValue(TEXT("RotationYaw")), EEasingFunc::Linear) };
	GEngine->AddOnScreenDebugMessage(11, 3.f, FColor::White, FString::Printf(TEXT("CurveValue : %f"), GetCurveValue(TEXT("RotationYaw"))));

	Player->SetActorRotation(FRotator{ 0.0, DeltaRotate, 0.0 });
}

void UACTAnimInstancePlayer::ResetTurnInPlace()
{
	//TurnInPlaceAngle = 0.f;
	//CurrentYaw = TargetYaw;
}

void UACTAnimInstancePlayer::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	if (Owner) {
		Player = Cast<AACTCharacterPlayer>(Owner);
	}

	OnMoveInputValueChanged.BindUObject(this, &UACTAnimInstancePlayer::SetMoveInputValue);

	LocomotionStateMachine = GetStateMachineInstanceFromName(LocomotionStateMachineName);
	CombatLocomotionStateMachine = GetStateMachineInstanceFromName(CombatLocomotionStateMachineName);
}

void UACTAnimInstancePlayer::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (Player) {
		RootMotionSpeed = FMath::Clamp(FMath::Abs(InputX) + FMath::Abs(InputY), 0.f, 2.f);

		Velocity = CharacterMovement->Velocity;
		GroundSpeed = Velocity.Size2D();
		Rotation = Owner->GetActorRotation();
		ControlRotation = Owner->GetControlRotation();
		AimRotation = Owner->GetBaseAimRotation();
		Direction = bIsMovementStop ? AbsoulteDirection : UKismetAnimationLibrary::CalculateDirection(Velocity, Rotation);

		// bIsIdle = GroundSpeed < MovingThreshould;
		bIsIdle = InputX == 0.f && InputY == 0.f;
		bIsArmed = Player->IsArmed();

		if (GroundSpeed > 10.f && !bIsMovementStop) {
			FRotator InterpolatedRotation{ FMath::RInterpTo(Rotation, ControlRotation, DeltaSeconds, 5.f) };
			InterpolatedRotation.Roll = InterpolatedRotation.Pitch = 0.f;
			Owner->SetActorRotation(InterpolatedRotation);
		}

		bIsMovementStop = IsMovementStop();
		if (bIsMovementStop) {
			AbsoulteDirection = Direction;
		}
	}
}

void UACTAnimInstancePlayer::BeginDestroy()
{
	Super::BeginDestroy();

	OnMoveInputValueChanged.Unbind();
}

void UACTAnimInstancePlayer::SetMoveInputValue(float NewInputX, float NewInputY)
{
	InputX = NewInputX;
	InputY = NewInputY;
}

bool UACTAnimInstancePlayer::IsMovementStop()
{
	GEngine->AddOnScreenDebugMessage(1, -1.f, FColor::Red, LocomotionStateMachine->GetCurrentStateName().ToString());
	GEngine->AddOnScreenDebugMessage(2, -1.f, FColor::Blue, CombatLocomotionStateMachine->GetCurrentStateName().ToString());

	FName CurrentStateName{ bIsArmed ? CombatLocomotionStateMachine->GetCurrentStateName() : LocomotionStateMachine->GetCurrentStateName() };
	GEngine->AddOnScreenDebugMessage(3, -1.f, FColor::Green, CurrentStateName.ToString());

	return  CurrentStateName == TEXT("StopWalk") || CurrentStateName == TEXT("StopRun");
}
