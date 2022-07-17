// Frontlines Game, All Rights Reserved

#include "Pickups/FLHealthPickup.h"
#include "Components/FLHealthComponent.h"

bool AFLHealthPickup::GivePickupTo(APawn *Pawn)
{
    Super::GivePickupTo(Pawn);

    const auto HealthComponent = FLUtils::GetCharacterComponent<UFLHealthComponent>(Pawn);
    if (!HealthComponent || HealthComponent->IsDead())
        return false;

    return HealthComponent->AddHealthFromPickup(HealthAmount);
}
