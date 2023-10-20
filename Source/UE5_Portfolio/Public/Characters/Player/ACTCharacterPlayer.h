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

protected:
	virtual void BeginPlay() override;

protected:	/* [Func] EnhancedInput */
	void Move(const FInputActionValue& InValue);
	void Look(const FInputActionValue& InValue);

protected:	/* Components */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	TObjectPtr<class USpringArmComponent> CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	TObjectPtr<class UCameraComponent> PlayerCamera;

protected:	/* EnhancedInput */
	UPROPERTY(EditAnywhere, Category = Input)
	TObjectPtr<class UInputMappingContext> DefaultMappingContext;

	UPROPERTY(EditAnywhere, Category = Input)
	TObjectPtr<class UInputAction> MoveAction;

	UPROPERTY(EditAnywhere, Category = Input)
	TObjectPtr<class UInputAction> LookAction;

	UPROPERTY(EditAnywhere, Category = Input)
	TObjectPtr<class UInputAction> JumpAction;
};
