// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/ACTAnimInstance.h"
#include "ACTAnimInstancePlayer.generated.h"

/**
 * 
 */
UCLASS()
class UE5_PORTFOLIO_API UACTAnimInstancePlayer : public UACTAnimInstance
{
	GENERATED_BODY()
	
public:
	UACTAnimInstancePlayer();

protected:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Character)
	TObjectPtr<class AACTCharacterPlayer> Player;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Character)
	uint8 bIsArmed : 1;
};
