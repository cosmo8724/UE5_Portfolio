#include "Weapons/ACTWeaponBase.h"

AACTWeaponBase::AACTWeaponBase()
{
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = Mesh;
}

void AACTWeaponBase::BeginPlay()
{
	Super::BeginPlay();
}

void AACTWeaponBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

