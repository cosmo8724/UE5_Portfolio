#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ACTWeaponBase.generated.h"

UCLASS()
class UE5_PORTFOLIO_API AACTWeaponBase : public AActor
{
	GENERATED_BODY()
	
public:	
	AACTWeaponBase();
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;

protected:
	UPROPERTY(EditDefaultsOnly, Category = Weapon)
	TObjectPtr<class UStaticMeshComponent> Mesh;
};
