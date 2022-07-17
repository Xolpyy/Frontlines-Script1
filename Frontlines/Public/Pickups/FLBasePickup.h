// Frontlines Game, All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FLBasePickup.generated.h"

class USphereComponent;
class UStaticMeshComponent;

UCLASS()
class FRONTLINES_API AFLBasePickup : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AFLBasePickup();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual bool GivePickupTo(APawn *Pawn);

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void NotifyActorBeginOverlap(AActor *OtherActor) override;

private:
	// Components
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	USphereComponent *SphereComponent = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent *StaticMeshComponent = nullptr;

	// Pickup
	FTimerHandle RespawnTimerHandle;
	float PickupRotationYaw;

	void OnPickupTaken();
	void Respawn();
	void GenerateRotation();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickups", meta = (AllowPrivateAccess = "true"))
	float RespawnTime = 5.f;
};
