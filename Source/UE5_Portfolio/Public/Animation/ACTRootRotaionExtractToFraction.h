// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AnimationModifier.h"
#include "ACTRootRotaionExtractToFraction.generated.h"

/**
 * 
 */
UCLASS()
class UE5_PORTFOLIO_API UACTRootRotaionExtractToFraction : public UAnimationModifier
{
	GENERATED_BODY()
	
public:
	virtual void OnApply_Implementation(UAnimSequence* AnimationSequence) override;
};
