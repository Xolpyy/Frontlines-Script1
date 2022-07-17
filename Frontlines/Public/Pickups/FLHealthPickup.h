// Frontlines Game, All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Pickups/FLBasePickup.h"
#include "FLUtils.h"
#include "FLHealthPickup.generated.h"

/**
 *
 */
UCLASS()
class FRONTLINES_API AFLHealthPickup : public AFLBasePickup
{
	GENERATED_BODY()

protected:
	virtual bool GivePickupTo(APawn *Pawn) override;

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health", meta = (AllowPrivateAccess = "true"))
	float HealthAmount = 100.f;
};
