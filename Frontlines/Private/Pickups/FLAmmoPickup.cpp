// Frontlines Game, All Rights Reserved

#include "Pickups/FLAmmoPickup.h"
#include "Components/FLHealthComponent.h"
#include "Components/FLWeaponComponent.h"
#include "Weapons/FLBaseWeapon.h"

bool AFLAmmoPickup::GivePickupTo(APawn *Pawn)
{
    Super::GivePickupTo(Pawn);

    const auto HealthComponent = FLUtils::GetCharacterComponent<UFLHealthComponent>(Pawn);
    if (!HealthComponent || HealthComponent->IsDead())
        return false;

    const auto WeaponComponent = FLUtils::GetCharacterComponent<UFLWeaponComponent>(Pawn);

    return WeaponComponent && WeaponComponent->AddAmmo(WeaponClass, ClipsAmount);
}
