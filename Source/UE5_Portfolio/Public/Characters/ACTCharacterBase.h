// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ACTCharacterBase.generated.h"

UCLASS()
class UE5_PORTFOLIO_API AACTCharacterBase : public ACharacter
{
	GENERATED_BODY()

public:
	AACTCharacterBase();

public:
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	virtual void BeginPlay() override;
};
