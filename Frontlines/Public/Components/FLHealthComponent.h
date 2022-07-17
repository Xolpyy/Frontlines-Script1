// Frontlines Game, All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "FLCoreTypes.h"
#include "FLHealthComponent.generated.h"

class UCameraShakeBase;

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class FRONTLINES_API UFLHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UFLHealthComponent();

	bool AddHealthFromPickup(float HealthAmount);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;

	// Health
	float GetHealthPercent() const { return Health / MaxHealth; }
	float GetHealth() const { return Health; }
	bool IsDead() const { return Health <= 0; }
	bool IsHealthFull() const { return Health >= MaxHealth; }

	// Delegates
	FOnHealthDecreasedSignature OnHealthDecreased;
	FOnHealthAddedSignature OnHealthAdded;
	FOnDeathSignature OnDeath;

private:
	// Health
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health", meta = (AllowPrivateAccess = "true"))
	float MaxHealth = 100.f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Health", meta = (AllowPrivateAccess = "true"))
	float Health;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health", meta = (AllowPrivateAccess = "true"))
	float CharacterLifeSpan = 60.f;

	// AutoHeal
	FTimerHandle HealingTimerHandle;

	void AddHealth();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Auto Heal", meta = (AllowPrivateAccess = "true"))
	bool bCanAutoHeal = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Auto Heal", meta = (AllowPrivateAccess = "true"))
	float AddedHealth = 3.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Auto Heal", meta = (AllowPrivateAccess = "true"))
	float HealingFrequency = 0.3f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Auto Heal", meta = (AllowPrivateAccess = "true"))
	float HealingDelay = 3.f;

	// Delegates
	UFUNCTION()
	void OnHit(AActor *DamagedActor, float Damage, const class UDamageType *DamageType, class AController *InstigatedBy, AActor *DamageCauser);

	// UI
	void PlayCameraShake();
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UCameraShakeBase> CameraShakeClass;
};
