// Frontlines Game, All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FLDamageActor.generated.h"

UCLASS()
class FRONTLINES_API AFLDamageActor : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AFLDamageActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sphere Settings", meta = (AllowPrivateAccess = "true"))
	FColor SphereColor = FColor::White;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sphere Settings", meta = (AllowPrivateAccess = "true"))
	float Damage = 2.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sphere Settings", meta = (AllowPrivateAccess = "true"))
	float SphereRadius = 300.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sphere Settings", meta = (AllowPrivateAccess = "true"))
	float SphereSegments = 20.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sphere Settings", meta = (AllowPrivateAccess = "true"))
	bool bApplyFullDamage = false;
};
