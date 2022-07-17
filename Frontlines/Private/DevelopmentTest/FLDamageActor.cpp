// Frontlines Game, All Rights Reserved

#include "DevelopmentTest/FLDamageActor.h"
#include "DrawDebugHelpers.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AFLDamageActor::AFLDamageActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AFLDamageActor::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AFLDamageActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	DrawDebugSphere(GetWorld(), GetActorLocation(), SphereRadius, SphereSegments, SphereColor);
	UGameplayStatics::ApplyRadialDamage(GetWorld(), Damage, GetActorLocation(), SphereRadius, nullptr, {}, this, GetInstigatorController(), bApplyFullDamage);
}
