// Frontlines Game, All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FLCoreTypes.h"
#include "FLBaseWeapon.generated.h"

class UNiagaraComponent;
class UNiagaraSystem;
class USkeletalMeshComponent;

UCLASS()
class FRONTLINES_API AFLBaseWeapon : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AFLBaseWeapon();

	FOnEmptyClipSignature OnEmptyClip;

	FWeaponUIData GetUIData() const { return UIData; }
	FAmmoData GetAmmoData() const { return CurrentAmmoData; }

	virtual void Shoot();
	virtual void StartShooting();
	virtual void StopShooting();

	void DecreaseAmmo();
	void ChangeClip();
	bool IsClipFull() const;
	bool IsAmmoEmpty() const;
	bool IsAmmoFull() const;

	bool AddAmmo(int32 ClipsAmount);

	// FX
	UNiagaraComponent *SpawnMuzzleFX() const;

	// Components
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	USceneComponent *SceneComponent = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	USkeletalMeshComponent *SkeletalMeshComponent = nullptr;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	AController *GetController() const;
	bool GetPlayerViewPoint(FVector &PlayerViewPointLocation, FRotator &PlayerViewPointRotation) const;
	bool GetTraceData(FHitResult &HitResult, FVector &LineTraceEnd) const;

	// Combat
	FTimerHandle ShootingTimerHandle;
	FVector GetMuzzleSocketLocation() const;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat", meta = (AllowPrivateAccess = "true"))
	FName MuzzleSocketName = TEXT("MuzzleSocket");

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat", meta = (AllowPrivateAccess = "true"))
	float ShotDistance = 10000.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat", meta = (AllowPrivateAccess = "true"))
	float Damage = 20.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat", meta = (AllowPrivateAccess = "true"))
	float ShotFrequency = 0.1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat", meta = (AllowPrivateAccess = "true"))
	float ShotRandomization = 0.5f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Visual Settings", meta = (AllowPrivateAccess = "true"))
	FColor HitColor = FColor::Red;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Visual Settings", meta = (AllowPrivateAccess = "true"))
	FColor MissColor = FColor::Blue;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Visual Settings", meta = (AllowPrivateAccess = "true"))
	float SphereRadius = 20.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Visual Settings", meta = (AllowPrivateAccess = "true"))
	float SphereSegments = 10.f;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	// Combat
	FAmmoData CurrentAmmoData;

	bool IsClipEmpty() const;
	void LogInfo();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon UI Data", meta = (AllowPrivateAccess = "true"))
	FWeaponUIData UIData;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ammo Data", meta = (AllowPrivateAccess = "true"))
	FAmmoData AmmoData{30, 3, false};

	// FX
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effects", meta = (AllowPrivateAccess = "true"))
	UNiagaraSystem *MuzzleEffect = nullptr;
};
