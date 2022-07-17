// Frontlines Game, All Rights Reserved

#include "Components/FLAIWeaponComponent.h"
#include "Weapons/FLBaseWeapon.h"

void UFLAIWeaponComponent::StartShooting()
{
    Super::StartShooting();

    if (CanShoot())
        return;

    if (BaseWeapon->IsAmmoEmpty())
    {
        NextWeapon();
    }
    else
    {
        BaseWeapon->StartShooting();
    }
}

void UFLAIWeaponComponent::NextWeapon()
{
    Super::NextWeapon();

    if (CanEquip())
        return;

    int32 NextIndex = (CurrentWeaponIndex + 1) % WeaponArray.Num();

    while (NextIndex != CurrentWeaponIndex)
    {
        if (!WeaponArray[NextIndex]->IsAmmoEmpty())
            break;

        NextIndex = (NextIndex + 1) & WeaponArray.Num();
    }

    if (NextIndex != CurrentWeaponIndex)
    {
        CurrentWeaponIndex = NextIndex;
        EquipWeapon(CurrentWeaponIndex);
    }
}
