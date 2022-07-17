// Frontlines Game, All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Weapons/FLBaseWeapon.h"
#include "FLLauncherWeapon.generated.h"

class AFLProjectileComponent;

/**
 *
 */
UCLASS()
class FRONTLINES_API AFLLauncherWeapon : public AFLBaseWeapon
{
	GENERATED_BODY()

public:
	virtual void Shoot() override;
	virtual void StartShooting() override;
	virtual void StopShooting() override;

private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Projectile", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<AFLProjectileComponent> ProjectileClass;
};
