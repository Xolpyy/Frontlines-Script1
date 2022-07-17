// Frontlines Game, All Rights Reserved

#include "Components/FLWeaponComponent.h"
#include "Animations/FLAnimUtils.h"
#include "Animations/FLOnEquipedAnimNotify.h"
#include "Animations/FLOnReloadedAnimNotify.h"
#include "Components/FLHealthComponent.h"
#include "Engine/World.h"
#include "GameFramework/Character.h"
#include "Player/FLBaseCharacter.h"
#include "Weapons/FLBaseWeapon.h"

// Sets default values for this component's properties
UFLWeaponComponent::UFLWeaponComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

// Called when the game starts
void UFLWeaponComponent::BeginPlay()
{
	Super::BeginPlay();

	SpawnWeapons();
	EquipWeapon(CurrentWeaponIndex);
	InitAnimations();
}

// Called every frame
void UFLWeaponComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UFLWeaponComponent::SpawnWeapons()
{
	if (!GetCharacterOwner())
		return;

	for (const auto Weapon : WeaponData)
	{
		BaseWeapon = GetWorld()->SpawnActor<AFLBaseWeapon>(Weapon.WeaponClass);
		if (!BaseWeapon)
			continue;

		AttachWeaponToComponent(BaseWeapon, GetCharacterOwner()->GetMesh(), HandSocketName);
		GetCharacterOwner()->HealthComponent->OnDeath.AddUObject(this, &UFLWeaponComponent::StopShooting);
		BaseWeapon->OnEmptyClip.AddUObject(this, &UFLWeaponComponent::OnEmptyClip);
		WeaponArray.Add(BaseWeapon);
		BaseWeapon->SetOwner(GetOwner());
	}
}

void UFLWeaponComponent::StartShooting()
{
	bWantsToShoot = true;

	if (CanShoot())
		return;

	BaseWeapon->StartShooting();
}

void UFLWeaponComponent::StopShooting()
{
	bWantsToShoot = false;

	BaseWeapon->StopShooting();
}

void UFLWeaponComponent::Shoot()
{
	BaseWeapon->Shoot();
}

void UFLWeaponComponent::NextWeapon()
{
	if (CanEquip())
		return;

	CurrentWeaponIndex = (CurrentWeaponIndex + 1) % WeaponArray.Num();
	EquipWeapon(CurrentWeaponIndex);
}

void UFLWeaponComponent::EquipWeapon(int32 WeaponIndex)
{
	if (WeaponIndex > WeaponArray.Num() || WeaponArray.Num() == 0 || !GetCharacterOwner())
		return;

	if (BaseWeapon)
	{
		StopShooting();
		AttachWeaponToComponent(BaseWeapon, GetCharacterOwner()->GetMesh(), ArmorySocketName);
	}

	BaseWeapon = WeaponArray[WeaponIndex];
	AttachWeaponToComponent(BaseWeapon, GetCharacterOwner()->GetMesh(), HandSocketName);
	PlayAnimMontage(EquipAnimMontage);

	const auto CurrentWeaponData = WeaponData.FindByPredicate([&](const FWeaponData &Data)
															  { return Data.WeaponClass == BaseWeapon->GetClass(); });

	CurrentReloadAnimMontage = CurrentWeaponData ? CurrentWeaponData->ReloadAnimMontage : nullptr;

	bWantsToEquip = true;
}

void UFLWeaponComponent::InitAnimations()
{
	const auto EquipNotify = FLAnimUtils::FindNotifyByClass<UFLOnEquipedAnimNotify>(EquipAnimMontage);
	if (EquipNotify)
	{
		EquipNotify->OnNotified.AddUObject(this, &UFLWeaponComponent::OnEquiped);
	}

	for (auto Notify : WeaponData)
	{
		const auto ReloadNotify = FLAnimUtils::FindNotifyByClass<UFLOnReloadedAnimNotify>(Notify.ReloadAnimMontage);
		if (ReloadNotify)
		{
			ReloadNotify->OnNotified.AddUObject(this, &UFLWeaponComponent::OnReloaded);
		}
	}
}

void UFLWeaponComponent::OnEquiped(USkeletalMeshComponent *Mesh)
{
	if (Mesh != GetCharacterOwner()->GetMesh())
		return;

	bWantsToEquip = false;
}

void UFLWeaponComponent::OnReloaded(USkeletalMeshComponent *Mesh)
{
	if (Mesh != GetCharacterOwner()->GetMesh())
		return;

	bWantsToReload = false;
}

void UFLWeaponComponent::OnEmptyClip(AFLBaseWeapon *CurrentWeapon)
{
	if (BaseWeapon == CurrentWeapon)
	{
		Reload();
	}
	else
	{
		for (auto Weapon : WeaponArray)
		{
			if (Weapon && Weapon == CurrentWeapon)
			{
				Weapon->ChangeClip();
			}
		}
	}
}

void UFLWeaponComponent::Reload()
{
	if (BaseWeapon->IsAmmoFull() || BaseWeapon->IsAmmoEmpty() || CanReload())
		return;

	StopShooting();
	BaseWeapon->ChangeClip();
	PlayAnimMontage(CurrentReloadAnimMontage);

	bWantsToReload = true;
}

bool UFLWeaponComponent::CanShoot() const
{
	return bWantsToEquip || bWantsToReload;
}

bool UFLWeaponComponent::CanEquip() const
{
	return bWantsToEquip || bWantsToReload;
}

bool UFLWeaponComponent::CanReload() const
{
	return bWantsToEquip || bWantsToReload;
}

void UFLWeaponComponent::PlayAnimMontage(UAnimMontage *Animation)
{
	GetCharacterOwner()->PlayAnimMontage(Animation);
}

void UFLWeaponComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	BaseWeapon = nullptr;

	for (const auto Weapon : WeaponArray)
	{
		Weapon->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
		Weapon->Destroy();
	}

	WeaponArray.Empty();
}

bool UFLWeaponComponent::GetUIData(FWeaponUIData &UIData) const
{
	if (BaseWeapon)
	{
		UIData = BaseWeapon->GetUIData();
		return true;
	}

	return false;
}

bool UFLWeaponComponent::GetAmmoData(FAmmoData &AmmoData) const
{
	if (BaseWeapon)
	{
		AmmoData = BaseWeapon->GetAmmoData();
		return true;
	}

	return false;
}

bool UFLWeaponComponent::AddAmmo(TSubclassOf<AFLBaseWeapon> WeaponClass, int32 ClipsAmount)
{
	for (auto Weapon : WeaponArray)
	{
		if (Weapon && Weapon->IsA(WeaponClass))
		{
			return Weapon->AddAmmo(ClipsAmount);
		}
	}

	return false;
}

void UFLWeaponComponent::AttachWeaponToComponent(AFLBaseWeapon *Weapon, USceneComponent *Component, FName SocketName)
{
	Weapon->AttachToComponent(Component, FAttachmentTransformRules::KeepRelativeTransform, SocketName);
}

AFLBaseCharacter *UFLWeaponComponent::GetCharacterOwner() const
{
	return Cast<AFLBaseCharacter>(GetOwner());
}
