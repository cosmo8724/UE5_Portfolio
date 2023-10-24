// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/ACTCharacterBase.h"
#include "InputActionValue.h"
#include "ACTCharacterPlayer.generated.h"

/**
 * 
 */
UCLASS()
class UE5_PORTFOLIO_API AACTCharacterPlayer : public AACTCharacterBase
{
	GENERATED_BODY()
	
public:
	AACTCharacterPlayer();

public:
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	const bool IsArmed() const { return bIsArmed; }

protected:
	virtual void BeginPlay() override;

protected:	/* [Func] EnhancedInput */
	void Move(const FInputActionValue& InValue);
	void Look(const FInputActionValue& InValue);
	void Armed();

protected:	/* [Func] Animation */
	void PlayIdleSwapMontage();

private:	/* [Func] Animation Notifies */
	UFUNCTION(BlueprintCallable)
	void IdleToCombatIdle();

	UFUNCTION(BlueprintCallable)
	void CombatIdleToIdle();

protected:	/* Components */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	TObjectPtr<class USpringArmComponent> CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	TObjectPtr<class UCameraComponent> PlayerCamera;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Weapon)
	TSubclassOf<class AACTWeaponBase> MainWeaponClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Weapon)
	TObjectPtr<class AACTWeaponBase> MainWeapon;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Weapon)
	TSubclassOf<class AACTWeaponBase> SubWeaponClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Weapon)
	TObjectPtr<class AACTWeaponBase> SubWeapon;

protected:	/* EnhancedInput */
	UPROPERTY(EditAnywhere, Category = Input)
	TObjectPtr<class UInputMappingContext> DefaultMappingContext;

	UPROPERTY(EditAnywhere, Category = Input)
	TObjectPtr<class UInputAction> MoveAction;

	UPROPERTY(EditAnywhere, Category = Input)
	TObjectPtr<class UInputAction> LookAction;

	UPROPERTY(EditAnywhere, Category = Input)
	TObjectPtr<class UInputAction> JumpAction;

	UPROPERTY(EditAnywhere, Category = Input)
	TObjectPtr<class UInputAction> ArmedAction;

protected:	/* Animation */
	UPROPERTY(EditDefaultsOnly, Category = Animation)
	TObjectPtr<class UAnimMontage> IdleSwapMontage;

protected:	/* Attributes */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Weapon)
	uint8 bIsArmed : 1;
};
