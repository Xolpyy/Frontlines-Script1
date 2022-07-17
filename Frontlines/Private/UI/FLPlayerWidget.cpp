// Frontlines Game, All Rights Reserved

#include "UI/FLPlayerWidget.h"
#include "Components/FLHealthComponent.h"
#include "Components/ProgressBar.h"
#include "Components/FLWeaponComponent.h"

void UFLPlayerWidget::NativeOnInitialized()
{
    Super::NativeOnInitialized();

    const auto HealthComponent = GetHealthComponent();
    if (HealthComponent)
    {
        HealthComponent->OnHealthDecreased.AddUObject(this, &UFLPlayerWidget::OnHealthDecreased);
        HealthComponent->OnHealthAdded.AddUObject(this, &UFLPlayerWidget::OnHealthAdded);
    }
}

void UFLPlayerWidget::SetHealth()
{
    const auto HealthComponent = GetHealthComponent();
    if (!HealthProgressBar || !HealthComponent)
        return;

    const auto Color = HealthComponent->GetHealthPercent() < LowHealthPercent ? BadColor : GoodColor;

    HealthProgressBar->SetPercent(HealthComponent->GetHealthPercent());
    HealthProgressBar->SetFillColorAndOpacity(Color);
}

void UFLPlayerWidget::OnHealthDecreased(float Health)
{
    if(!IsAnimationPlaying(DamageImageAnimation))
    {
        PlayAnimation(DamageImageAnimation);
    }

    SetHealth();
}

void UFLPlayerWidget::OnHealthAdded(float Health)
{
    SetHealth();
}

bool UFLPlayerWidget::GetUIData(FWeaponUIData &UIData) const
{
    const auto WeaponComponent = GetWeaponComponent();
    if (!WeaponComponent)
        return false;

    return WeaponComponent->GetUIData(UIData);
}

bool UFLPlayerWidget::GetAmmoData(FAmmoData &AmmoData) const
{
    const auto WeaponComponent = GetWeaponComponent();
    if (!WeaponComponent)
        return false;

    return WeaponComponent->GetAmmoData(AmmoData);
}

bool UFLPlayerWidget::IsPlayerSpectating() const
{
    const auto Controller = GetOwningPlayer();
    return Controller && Controller->GetStateName() == NAME_Spectating;
}

bool UFLPlayerWidget::IsPlayerDead() const
{
    const auto HealthComponent = GetHealthComponent();

    return HealthComponent && HealthComponent->IsDead();
}

UFLHealthComponent *UFLPlayerWidget::GetHealthComponent() const
{
    return FLUtils::GetCharacterComponent<UFLHealthComponent>(GetOwningPlayerPawn());
}

UFLWeaponComponent *UFLPlayerWidget::GetWeaponComponent() const
{
    return FLUtils::GetCharacterComponent<UFLWeaponComponent>(GetOwningPlayerPawn());
}
