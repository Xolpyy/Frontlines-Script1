// Frontlines Game, All Rights Reserved

#include "Pickups/FLBasePickup.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/World.h"
#include "TimerManager.h"

// Sets default values
AFLBasePickup::AFLBasePickup()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SceneComponent"));
	SphereComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
	SphereComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	SphereComponent->SetVisibility(false, false);
	SphereComponent->SetSphereRadius(48.0);
	SetRootComponent(SphereComponent);

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	StaticMeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	StaticMeshComponent->SetupAttachment(GetRootComponent());
}

// Called when the game starts or when spawned
void AFLBasePickup::BeginPlay()
{
	Super::BeginPlay();

	GenerateRotation();
}

// Called every frame
void AFLBasePickup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AddActorLocalRotation(FRotator(0.f, PickupRotationYaw, 0.f));
}

void AFLBasePickup::NotifyActorBeginOverlap(AActor *OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	APawn *Pawn = Cast<APawn>(OtherActor);

	if (GivePickupTo(Pawn))
	{
		OnPickupTaken();
	}
}

void AFLBasePickup::OnPickupTaken()
{
	SphereComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	StaticMeshComponent->SetVisibility(false, true);

	GetWorld()->GetTimerManager().SetTimer(RespawnTimerHandle, this, &AFLBasePickup::Respawn, RespawnTime);
}

void AFLBasePickup::Respawn()
{
	SphereComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
	StaticMeshComponent->SetVisibility(true, true);

	GetWorld()->GetTimerManager().ClearTimer(RespawnTimerHandle);
	GenerateRotation();
}

void AFLBasePickup::GenerateRotation()
{
	const float Direction = FMath::RandBool() ? 1.f : -1.f;
	PickupRotationYaw = FMath::RandRange(0.f, 1.f) * Direction;
}

bool AFLBasePickup::GivePickupTo(APawn *Pawn)
{
	return true;
}
