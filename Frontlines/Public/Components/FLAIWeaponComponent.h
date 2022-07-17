// Frontlines Game, All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Components/FLWeaponComponent.h"
#include "FLAIWeaponComponent.generated.h"

/**
 *
 */
UCLASS()
class FRONTLINES_API UFLAIWeaponComponent : public UFLWeaponComponent
{
	GENERATED_BODY()

public:
	virtual void StartShooting() override;
	virtual void NextWeapon() override;
};
