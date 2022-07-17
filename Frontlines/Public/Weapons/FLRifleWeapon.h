// Frontlines Game, All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Weapons/FLBaseWeapon.h"
#include "FLRifleWeapon.generated.h"

class UFLWeaponFXComponent;

/**
 *
 */
UCLASS()
class FRONTLINES_API AFLRifleWeapon : public AFLBaseWeapon
{
	GENERATED_BODY()

public:
	AFLRifleWeapon();

	virtual void Shoot() override;
	virtual void StartShooting() override;
	virtual void StopShooting() override;

private:
	void EffectsInit();
	void PauseEffects(bool bIsPaused);
	void SpawnTraceFX(const FVector &TraceStart, const FVector &TraceEnd);

	// Components

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UFLWeaponFXComponent *WeaponFXComponent = nullptr;

	// FX
	UPROPERTY()
	UNiagaraComponent *MuzzleFXComponent = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effects", meta = (AllowPrivateAccess = "true"))
	FString TraceEffectName = TEXT("TraceTarget");

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effects", meta = (AllowPrivateAccess = "true"))
	UNiagaraSystem *TraceEffect = nullptr;

};
