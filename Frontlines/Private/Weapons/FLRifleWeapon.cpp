// Frontlines Game, All Rights Reserved

#include "Weapons/FLRifleWeapon.h"
#include "Components/FLWeaponFXComponent.h"
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"

AFLRifleWeapon::AFLRifleWeapon()
{
    WeaponFXComponent = CreateDefaultSubobject<UFLWeaponFXComponent>(TEXT("WeaponFXComponent"));
}

void AFLRifleWeapon::StartShooting()
{
    Super::StartShooting();

    EffectsInit();
    GetWorld()->GetTimerManager().SetTimer(ShootingTimerHandle, this, &AFLBaseWeapon::Shoot, ShotFrequency, true);
    Shoot();
}

void AFLRifleWeapon::StopShooting()
{
    Super::StopShooting();

    GetWorld()->GetTimerManager().ClearTimer(ShootingTimerHandle);
    PauseEffects(true);
}

void AFLRifleWeapon::Shoot()
{
    Super::Shoot();

    if (IsAmmoEmpty())
        return;

    FHitResult HitResult;
    FVector LineTraceEnd;

    if (!GetTraceData(HitResult, LineTraceEnd))
        return;

    FVector TraceEnd = LineTraceEnd;
    if (HitResult.bBlockingHit)
    {
        TraceEnd = HitResult.ImpactPoint;
        if (const auto DamagedActor = HitResult.GetActor())
        {
            DamagedActor->TakeDamage(Damage, FDamageEvent(), GetController(), this);
        }

        WeaponFXComponent->SpawnFX(HitResult);
    }

    SpawnTraceFX(GetMuzzleSocketLocation(), TraceEnd);
    DecreaseAmmo();
}

void AFLRifleWeapon::EffectsInit()
{
    if (!MuzzleFXComponent)
    {
        MuzzleFXComponent = SpawnMuzzleFX();
    }

    PauseEffects(false);
}

void AFLRifleWeapon::PauseEffects(bool bIsPaused)
{
    if (MuzzleFXComponent)
    {
        MuzzleFXComponent->SetPaused(bIsPaused);
        MuzzleFXComponent->SetVisibility(!bIsPaused, true);
    }
}

void AFLRifleWeapon::SpawnTraceFX(const FVector &TraceStart, const FVector &TraceEnd)
{
    auto TraceFXComponent = UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(),           //
                                                                           TraceEffect,          //
                                                                           TraceStart,           //
                                                                           FRotator::ZeroRotator //
    );

    if (TraceFXComponent)
    {
        TraceFXComponent->SetNiagaraVariableVec3(TraceEffectName, TraceEnd);
    }
}
