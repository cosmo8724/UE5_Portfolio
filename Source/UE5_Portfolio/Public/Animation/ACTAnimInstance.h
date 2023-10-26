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

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Character)
	FVector Velocity;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Character)
	float GroundSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Character)
	FRotator Rotation;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Character)
	FRotator ControlRotation;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Character)
	FRotator AimRotation;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Character)
	float Direction;

	float AbsoulteDirection;

	uint8 bIsMovementStop;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Character)
	uint8 bIsIdle : 1;

	UPROPERTY(EditDefaultsOnly, Category = StateMachine)
	FName LocomotionStateMachineName;

	UPROPERTY(EditDefaultsOnly, Category = StateMachine)
	FName CombatLocomotionStateMachineName;
};
