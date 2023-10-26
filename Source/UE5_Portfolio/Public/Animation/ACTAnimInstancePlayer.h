// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/ACTAnimInstance.h"
#include "ACTAnimInstancePlayer.generated.h"

DECLARE_DELEGATE_TwoParams(FOnMoveInputValueChanged, float /* InputX */, float /* InputY */);

/**
 * 
 */
UCLASS()
class UE5_PORTFOLIO_API UACTAnimInstancePlayer : public UACTAnimInstance
{
	GENERATED_BODY()
	
public:
	UACTAnimInstancePlayer();

public:
	void ExecuteOnMoveInputValueChanged(float NewInputX, float NewInputY);
	void SetTurnInPlace(double InTurnInPlaceAngle, double InCurrentYaw, double InTargetYaw);

	UFUNCTION(BlueprintCallable)
	void ExecuteTurnInPlace();

	UFUNCTION(BlueprintCallable)
	void ResetTurnInPlace();

protected:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
	virtual void BeginDestroy() override;

private:
	void SetMoveInputValue(float NewInputX, float NewInputY);
	bool IsMovementStop();

protected:	/* Delegates */
	FOnMoveInputValueChanged OnMoveInputValueChanged;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Character)
	TObjectPtr<class AACTCharacterPlayer> Player;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = StateProperties)
	uint8 bIsArmed : 1;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = TurnInPlace)
	uint8 bIsNeedTurnInPlace : 1;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = TurnInPlace)
	float TurnInPlaceAngle;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = TurnInPlace)
	float CurrentYaw;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = TurnInPlace)
	float TargetYaw;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Movement)
	float InputX;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Movement)
	float InputY;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Movement)
	float RootMotionSpeed;

private:
	TObjectPtr<const FAnimNode_StateMachine> LocomotionStateMachine;
	TObjectPtr<const FAnimNode_StateMachine> CombatLocomotionStateMachine;
};
