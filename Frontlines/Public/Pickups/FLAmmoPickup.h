// Frontlines Game, All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Pickups/FLBasePickup.h"
#include "FLUtils.h"
#include "FLAmmoPickup.generated.h"

class AFLBaseWeapon;

/**
 *
 */
UCLASS()
class FRONTLINES_API AFLAmmoPickup : public AFLBasePickup
{
	GENERATED_BODY()

protected:
	virtual bool GivePickupTo(APawn *Pawn) override;

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickups", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<AFLBaseWeapon> WeaponClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickups", meta = (AllowPrivateAccess = "true"))
	int32 ClipsAmount = 3.f;
};
