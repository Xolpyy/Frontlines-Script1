// Frontlines Game, All Rights Reserved

#include "Components/FLWeaponFXComponent.h"
#include "Engine/World.h"
#include "Components/DecalComponent.h"
#include "Kismet/GameplayStatics.h"
#include "NiagaraFunctionLibrary.h"
#include "PhysicalMaterials/PhysicalMaterial.h"

// Sets default values for this component's properties
UFLWeaponFXComponent::UFLWeaponFXComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}

// Called when the game starts
void UFLWeaponFXComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
}

// Called every frame
void UFLWeaponFXComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UFLWeaponFXComponent::SpawnFX(const FHitResult &Hit)
{
	auto Effect = EffectData;

	if (Hit.PhysMaterial.IsValid())
	{
		const auto PhysMat = Hit.PhysMaterial.Get();
		if (EffectsMap.Contains(PhysMat))
		{
			Effect = EffectsMap[PhysMat];
		}
	}

	// Effect Spawn
	UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(),				   //
												   Effect.DefaultEffect,	   //
												   Hit.ImpactPoint,			   //
												   Hit.ImpactNormal.Rotation() //
	);

	// Decal Spawn
	auto DecalComponent = UGameplayStatics::SpawnDecalAtLocation(GetWorld(),					 //
																 Effect.DecalData.Material, //
																 Effect.DecalData.Size,	 //
																 Hit.ImpactPoint,				 //
																 Hit.ImpactNormal.Rotation()	 //
	);

	if (DecalComponent)
	{
		DecalComponent->SetFadeOut(Effect.DecalData.LifeTime, Effect.DecalData.FadeOutTime);
	}
}
