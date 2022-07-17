// Frontlines Game, All Rights Reserved

#include "Weapons/FLProjectileComponent.h"
#include "Components/FLWeaponFXComponent.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "DrawDebugHelpers.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "NiagaraComponent.h"

// Sets default values
AFLProjectileComponent::AFLProjectileComponent()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	SphereComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	SphereComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
	SphereComponent->bReturnMaterialOnMove = true;
	SetRootComponent(SphereComponent);

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	StaticMeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	StaticMeshComponent->SetupAttachment(GetRootComponent());

	TraceFXComponent = CreateDefaultSubobject<UNiagaraComponent>(TEXT("TraceFXComponent"));
	TraceFXComponent->SetActive(true);
	TraceFXComponent->SetupAttachment(GetRootComponent());

	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));

	WeaponFXComponent = CreateDefaultSubobject<UFLWeaponFXComponent>(TEXT("WeaponFXComponent"));
}

// Called when the game starts or when spawned
void AFLProjectileComponent::BeginPlay()
{
	Super::BeginPlay();

	ProjectileMovementComponent->Velocity = Direction * ProjectileMovementComponent->InitialSpeed;

	SetLifeSpan(ProjectileLifeSpan);

	SphereComponent->OnComponentHit.AddDynamic(this, &AFLProjectileComponent::OnHit);
}

// Called every frame
void AFLProjectileComponent::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AFLProjectileComponent::OnHit(UPrimitiveComponent *HitComponent, AActor *OtherActor, UPrimitiveComponent *OtherComp, FVector NormalImpulse, const FHitResult &Hit)
{
	ProjectileMovementComponent->StopMovementImmediately();
	const auto Pawn = Cast<APawn>(GetOwner());

	if (!OtherActor || OtherActor == this || !Pawn || !GetWorld())
		return;

	UGameplayStatics::ApplyRadialDamage(GetWorld(), SphereDamage, GetActorLocation(), SphereRadius, nullptr, {}, this, Pawn->Controller, bApplyFullDamage);

	WeaponFXComponent->SpawnFX(Hit);

	Destroy();
}
