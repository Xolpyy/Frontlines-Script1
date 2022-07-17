// Frontlines Game, All Rights Reserved

#include "Weapons/FLLauncherWeapon.h"
#include "Engine/World.h"
#include "Weapons/FLProjectileComponent.h"

void AFLLauncherWeapon::StartShooting()
{
    Super::StartShooting();

    Shoot();
}

void AFLLauncherWeapon::StopShooting()
{
    Super::StopShooting();
}

void AFLLauncherWeapon::Shoot()
{
    Super::Shoot();

    if (IsAmmoEmpty())
        return;

    FHitResult HitResult;
    FVector LineTraceEnd;
    if (!GetTraceData(HitResult, LineTraceEnd) || !ProjectileClass)
        return;

    const FTransform SpawnTransform(FRotator::ZeroRotator, GetMuzzleSocketLocation());

    const FVector EndPoint = HitResult.bBlockingHit ? HitResult.ImpactPoint : LineTraceEnd;
    const FVector ShotDirection = FVector(EndPoint - GetMuzzleSocketLocation()).GetSafeNormal();

    auto ProjectileComponent = GetWorld()->SpawnActorDeferred<AFLProjectileComponent>(ProjectileClass, SpawnTransform);

    if (ProjectileComponent)
    {
        ProjectileComponent->SetShotDirection(ShotDirection);
        ProjectileComponent->SetOwner(GetOwner());
        ProjectileComponent->FinishSpawning(SpawnTransform);
    }

    DecreaseAmmo();
    SpawnMuzzleFX();
}
