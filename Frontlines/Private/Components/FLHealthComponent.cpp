// Frontlines Game, All Rights Reserved

#include "Components/FLHealthComponent.h"
#include "Camera/PlayerCameraManager.h"
#include "Components/CapsuleComponent.h"
#include "Engine/World.h"
#include "GameFramework/Controller.h"
#include "Player/FLBaseCharacter.h"
#include "TimerManager.h"

// Sets default values for this component's properties
UFLHealthComponent::UFLHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

// Called when the game starts
void UFLHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	Health = MaxHealth;

	GetOwner()->OnTakeAnyDamage.AddDynamic(this, &UFLHealthComponent::OnHit);
}

// Called every frame
void UFLHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UFLHealthComponent::OnHit(AActor *DamagedActor, float Damage, const class UDamageType *DamageType, class AController *InstigatedBy, AActor *DamageCauser)
{
	const auto Character = Cast<AFLBaseCharacter>(GetOwner());

	if (IsDead() || Damage == 0 || !Character)
		return;

	Health = FMath::Clamp(Health - Damage, 0.0f, MaxHealth);

	OnHealthDecreased.Broadcast(Health);

	if (IsDead())
	{
		OnDeath.Broadcast();
		GetWorld()->GetTimerManager().ClearTimer(HealingTimerHandle);
		Character->GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		Character->GetMesh()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		Character->GetMesh()->SetSimulatePhysics(true);
		Character->GetController()->ChangeState(NAME_Spectating);
		Character->SetLifeSpan(CharacterLifeSpan);
		Character->DetachFromControllerPendingDestroy();
	}
	else if (GetWorld() && bCanAutoHeal)
	{
		GetWorld()->GetTimerManager().SetTimer(HealingTimerHandle, this, &UFLHealthComponent::AddHealth, HealingFrequency, true, HealingDelay);
	}

	PlayCameraShake();
}

void UFLHealthComponent::AddHealth()
{
	Health = FMath::Min(Health + AddedHealth, MaxHealth);

	OnHealthAdded.Broadcast(Health);

	if (GetWorld() && IsHealthFull())
	{
		GetWorld()->GetTimerManager().ClearTimer(HealingTimerHandle);
	}
}

bool UFLHealthComponent::AddHealthFromPickup(float HealthAmount)
{
	if (IsHealthFull())
		return false;

	Health = FMath::Min(HealthAmount + Health, MaxHealth);
	OnHealthAdded.Broadcast(Health);

	return true;
}

void UFLHealthComponent::PlayCameraShake()
{
	const auto Pawn = Cast<APawn>(GetOwner());
	if (!Pawn)
		return;

	const auto Controller = Pawn->GetController<APlayerController>();
	if (!Controller || !Controller->PlayerCameraManager)
		return;

	Controller->PlayerCameraManager->StartCameraShake(CameraShakeClass);
}
