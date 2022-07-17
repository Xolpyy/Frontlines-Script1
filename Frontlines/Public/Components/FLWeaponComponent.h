// Frontlines Game, All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "FLCoreTypes.h"
#include "FLWeaponComponent.generated.h"

class AFLBaseCharacter;
class AFLBaseWeapon;
class USkeletalMeshComponent;

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class FRONTLINES_API UFLWeaponComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UFLWeaponComponent();

	bool WantsToShoot() const { return bWantsToShoot; }

	void Shoot();
	virtual void StartShooting();
	void StopShooting();

	virtual void NextWeapon();
	void Reload();

	bool GetUIData(FWeaponUIData &UIData) const;
	bool GetAmmoData(FAmmoData &AmmoData) const;

	bool AddAmmo(TSubclassOf<AFLBaseWeapon> WeaponClass, int32 AmmoAmount);
	
	UPROPERTY()
	AFLBaseWeapon *BaseWeapon = nullptr;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	void EquipWeapon(int32 WeaponIndex);
	
	bool CanShoot() const;
	bool CanEquip() const;

	int32 CurrentWeaponIndex = 0;

	UPROPERTY()
	TArray<AFLBaseWeapon *> WeaponArray;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;

private:
	bool bWantsToEquip = false;
	bool bWantsToShoot = false;
	bool bWantsToReload = false;

	bool CanReload() const;

	void SpawnWeapons();
	void AttachWeaponToComponent(AFLBaseWeapon *Weapon, USceneComponent *Component, FName SocketName);
	void InitAnimations();
	void OnEquiped(USkeletalMeshComponent *Mesh);
	void OnReloaded(USkeletalMeshComponent *Mesh);
	void OnEmptyClip(AFLBaseWeapon *CurrentWeapon);
	void PlayAnimMontage(UAnimMontage *Animation);
	AFLBaseCharacter *GetCharacterOwner() const;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon", meta = (AllowPrivateAccess = "true"))
	TArray<FWeaponData> WeaponData;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon", meta = (AllowPrivateAccess = "true"))
	FName HandSocketName = TEXT("WeaponSocket");

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon", meta = (AllowPrivateAccess = "true"))
	FName ArmorySocketName = TEXT("ArmorySocket");

	UPROPERTY()
	UAnimMontage *CurrentReloadAnimMontage = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation", meta = (AllowPrivateAccess = "true"))
	UAnimMontage *EquipAnimMontage = nullptr;
};
