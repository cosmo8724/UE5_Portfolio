// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "ACTAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class UE5_PORTFOLIO_API UACTAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	UACTAnimInstance();

protected:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Character)
	TObjectPtr<class ACharacter> Owner;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Character)
	TObjectPtr<class UCharacterMovementComponent> CharacterMovement;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Character)
	float MovingThreshould{ 3.f };

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Movement)
	FVector Velocity;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Movement)
	float GroundSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Rotation)
	FRotator Rotation;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Rotation)
	FRotator ControlRotation;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Rotation)
	FRotator AimRotation;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Movement)
	float Direction;

	float AbsoulteDirection;

	uint8 bIsMovementStop;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = StateProperties)
	uint8 bIsIdle : 1;

	UPROPERTY(EditDefaultsOnly, Category = StateMachine)
	FName LocomotionStateMachineName;

	UPROPERTY(EditDefaultsOnly, Category = StateMachine)
	FName CombatLocomotionStateMachineName;
};
