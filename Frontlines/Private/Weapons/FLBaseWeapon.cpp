// Frontlines Game, All Rights Reserved

#include "Weapons/FLBaseWeapon.h"
#include "Components/SkeletalMeshComponent.h"
#include "DrawDebugHelpers.h"
#include "Engine/World.h"
#include "GameFramework/Controller.h"
#include "GameFramework/Character.h"
#include "NiagaraFunctionLibrary.h"
#include "TimerManager.h"

DEFINE_LOG_CATEGORY_STATIC(BaseWeaponLog, All, All);

// Sets default values
AFLBaseWeapon::AFLBaseWeapon()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
	SetRootComponent(SceneComponent);

	SkeletalMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMeshComponent"));
	SkeletalMeshComponent->SetupAttachment(GetRootComponent());
}

// Called when the game starts or when spawned
void AFLBaseWeapon::BeginPlay()
{
	Super::BeginPlay();

	CurrentAmmoData = AmmoData;
}

// Called every frame
void AFLBaseWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AFLBaseWeapon::StartShooting()
{
}

void AFLBaseWeapon::StopShooting()
{
}

void AFLBaseWeapon::Shoot()
{
}

AController *AFLBaseWeapon::GetController() const
{
	const auto Character = Cast<APawn>(GetOwner());
	if (!Character)
		return nullptr;

	return Character->GetController();
}

bool AFLBaseWeapon::GetPlayerViewPoint(FVector &PlayerViewPointLocation, FRotator &PlayerViewPointRotation) const
{
	const auto Character = Cast<APawn>(GetOwner());
	if (!Character)
		return false;

	if (Character->IsPlayerControlled())
	{
		const auto Controller = GetController();
		if (!Controller)
			return false;

		Controller->GetPlayerViewPoint(PlayerViewPointLocation, PlayerViewPointRotation);
	}
	else
	{
		PlayerViewPointLocation = GetMuzzleSocketLocation();
		PlayerViewPointRotation = SkeletalMeshComponent->GetSocketRotation(MuzzleSocketName);
	}

	return true;
}

bool AFLBaseWeapon::GetTraceData(FHitResult &HitResult, FVector &LineTraceEnd) const
{
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;
	if (!GetPlayerViewPoint(PlayerViewPointLocation, PlayerViewPointRotation))
		return false;

	auto ShotSpread = FMath::RadiansToDegrees(ShotRandomization);
	LineTraceEnd = PlayerViewPointLocation + FMath::VRandCone(PlayerViewPointRotation.Vector(), ShotSpread) * ShotDistance;

	FCollisionQueryParams QueryParams;
	QueryParams.bReturnPhysicalMaterial = true;
	QueryParams.AddIgnoredActor(GetOwner());
	QueryParams.AddIgnoredActor(this);
	GetWorld()->LineTraceSingleByChannel(HitResult,							//
										 PlayerViewPointLocation,			//
										 LineTraceEnd,						//
										 ECollisionChannel::ECC_Visibility, //
										 QueryParams						//
	);

	return true;
}

void AFLBaseWeapon::DecreaseAmmo()
{
	CurrentAmmoData.Bullets--;

	if (IsClipEmpty())
	{
		OnEmptyClip.Broadcast(this);
	}
}

void AFLBaseWeapon::ChangeClip()
{
	CurrentAmmoData.Bullets = AmmoData.Bullets;

	if (!CurrentAmmoData.bInfinite)
	{
		CurrentAmmoData.Clips--;
	}
}

bool AFLBaseWeapon::IsClipEmpty() const
{
	return CurrentAmmoData.Bullets == 0;
}

bool AFLBaseWeapon::IsClipFull() const
{
	return CurrentAmmoData.Clips == AmmoData.Clips;
}

bool AFLBaseWeapon::IsAmmoEmpty() const
{
	return IsClipEmpty() &&
		   CurrentAmmoData.Clips == 0;
}

bool AFLBaseWeapon::IsAmmoFull() const
{
	return CurrentAmmoData.Bullets == AmmoData.Bullets;
}

void AFLBaseWeapon::LogInfo()
{
	FString InfiniteAmmoInfo = CurrentAmmoData.bInfinite ? TEXT("Infinite") : FString::FromInt(CurrentAmmoData.Clips);
	FString AmmoInfo = FString::FromInt(CurrentAmmoData.Bullets) + TEXT("/") + InfiniteAmmoInfo;
	UE_LOG(BaseWeaponLog, Display, TEXT("%s"), *AmmoInfo);
}

FVector AFLBaseWeapon::GetMuzzleSocketLocation() const
{
	return SkeletalMeshComponent->GetSocketLocation(MuzzleSocketName);
}

bool AFLBaseWeapon::AddAmmo(int32 ClipsAmount)
{
	if (ClipsAmount <= 0 || IsClipFull() || CurrentAmmoData.bInfinite)
		return false;

	if (IsAmmoEmpty())
	{
		CurrentAmmoData.Clips = FMath::Min(ClipsAmount, AmmoData.Clips + 1);
		OnEmptyClip.Broadcast(this);
	}
	else if (CurrentAmmoData.Clips < AmmoData.Clips)
	{
		int32 NextClipsAmount = CurrentAmmoData.Clips + ClipsAmount;
		if (AmmoData.Clips - NextClipsAmount >= 0)
		{
			CurrentAmmoData.Clips = NextClipsAmount;
		}
		else
		{
			CurrentAmmoData.Clips = AmmoData.Clips;
			CurrentAmmoData.Bullets = AmmoData.Bullets;
		}
	}
	else
	{
		CurrentAmmoData.Bullets = AmmoData.Bullets;
	}

	return true;
}

UNiagaraComponent *AFLBaseWeapon::SpawnMuzzleFX() const
{
	return UNiagaraFunctionLibrary::SpawnSystemAttached(MuzzleEffect,				   //
														SkeletalMeshComponent,		   //
														MuzzleSocketName,			   //
														FVector::ZeroVector,		   //
														FRotator::ZeroRotator,		   //
														EAttachLocation::SnapToTarget, //
														true						   //
	);
}
