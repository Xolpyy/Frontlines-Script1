// Frontlines Game, All Rights Reserved

#include "Player/FLBaseCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/FLCharacterMovementComponent.h"
#include "Components/FLHealthComponent.h"
#include "Components/TextRenderComponent.h"
#include "Components/FLWeaponComponent.h"
#include "Engine/World.h"
#include "GameFramework/Character.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Weapons/FLBaseWeapon.h"

// Sets default values
AFLBaseCharacter::AFLBaseCharacter(const FObjectInitializer &ObjectInit)
	: Super(ObjectInit.SetDefaultSubobjectClass<UFLCharacterMovementComponent>(ACharacter::CharacterMovementComponentName))
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent"));
	SpringArmComponent->bUsePawnControlRotation = true;
	SpringArmComponent->SetupAttachment(GetRootComponent());

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	CameraComponent->SetupAttachment(SpringArmComponent);

	HealthComponent = CreateDefaultSubobject<UFLHealthComponent>(TEXT("HealthComponent"));

	WeaponComponent = CreateDefaultSubobject<UFLWeaponComponent>(TEXT("WeaponComponent"));
}

// Called when the game starts or when spawned
void AFLBaseCharacter::BeginPlay()
{
	Super::BeginPlay();

	LandedDelegate.AddDynamic(this, &AFLBaseCharacter::OnGroundLanded);
}

// Called every frame
void AFLBaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AFLBaseCharacter::SetupPlayerInputComponent(UInputComponent *PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &AFLBaseCharacter::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &AFLBaseCharacter::MoveRight);
	PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &AFLBaseCharacter::LookUp);
	PlayerInputComponent->BindAxis(TEXT("LookRight"), this, &AFLBaseCharacter::LookRight);
	PlayerInputComponent->BindAxis(TEXT("LookUpRate"), this, &AFLBaseCharacter::LookUpRate);
	PlayerInputComponent->BindAxis(TEXT("LookRightRate"), this, &AFLBaseCharacter::LookRightRate);

	PlayerInputComponent->BindAction(TEXT("Jump"), EInputEvent::IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction(TEXT("Run"), EInputEvent::IE_Pressed, this, &AFLBaseCharacter::StartRunning);
	PlayerInputComponent->BindAction(TEXT("Run"), EInputEvent::IE_Released, this, &AFLBaseCharacter::StopRunning);
	PlayerInputComponent->BindAction(TEXT("Shoot"), EInputEvent::IE_Pressed, WeaponComponent, &UFLWeaponComponent::StartShooting);
	PlayerInputComponent->BindAction(TEXT("Shoot"), EInputEvent::IE_Released, WeaponComponent, &UFLWeaponComponent::StopShooting);
	PlayerInputComponent->BindAction(TEXT("NextWeapon"), EInputEvent::IE_Pressed, WeaponComponent, &UFLWeaponComponent::NextWeapon);
	PlayerInputComponent->BindAction(TEXT("Reload"), EInputEvent::IE_Pressed, WeaponComponent, &UFLWeaponComponent::Reload);
}

void AFLBaseCharacter::MoveForward(float AxisValue)
{
	bIsMovingForward = AxisValue > 0.0f;
	AddMovementInput(GetActorForwardVector(), AxisValue);
}

void AFLBaseCharacter::MoveRight(float AxisValue)
{
	bIsNotMovingRight = AxisValue == 0.0f;
	AddMovementInput(GetActorRightVector(), AxisValue);
}

void AFLBaseCharacter::LookUp(float AxisValue)
{
	AddControllerPitchInput(AxisValue * LookUpRateValue * GetWorld()->GetDeltaSeconds());
}

void AFLBaseCharacter::LookRight(float AxisValue)
{
	AddControllerYawInput(AxisValue * LookRightRateValue * GetWorld()->GetDeltaSeconds());
}

void AFLBaseCharacter::LookUpRate(float AxisValue)
{
	AddControllerPitchInput(AxisValue * LookUpRateValue * GetWorld()->GetDeltaSeconds());
}

void AFLBaseCharacter::LookRightRate(float AxisValue)
{
	AddControllerYawInput(AxisValue * LookRightRateValue * GetWorld()->GetDeltaSeconds());
}

void AFLBaseCharacter::StartRunning()
{
	bWantsToRun = true;
}

void AFLBaseCharacter::StopRunning()
{
	bWantsToRun = false;
}

bool AFLBaseCharacter::IsRunning() const
{
	return bWantsToRun && bIsMovingForward && bIsNotMovingRight && !WeaponComponent->WantsToShoot() && !GetVelocity().IsZero();
}

void AFLBaseCharacter::OnGroundLanded(const FHitResult &Hit)
{
	const auto VelocityZ = -GetVelocity().Z;
	if (VelocityZ < LandedDamageVelocity.X)
		return;

	const auto FinalDamage = FMath::GetMappedRangeValueClamped(LandedDamageVelocity, LandedDamageAmount, VelocityZ);
	TakeDamage(FinalDamage, FDamageEvent(), nullptr, nullptr);
}

void AFLBaseCharacter::SetPlayerColor(const FLinearColor &Color)
{
	const auto MaterialInstance = GetMesh()->CreateAndSetMaterialInstanceDynamic(0);
	if (!MaterialInstance)
		return;

	MaterialInstance->SetVectorParameterValue(PlayerColorName, Color);
}

void AFLBaseCharacter::SetWeaponColor(const FLinearColor &Color)
{
	const auto MaterialInstace1 = WeaponComponent->BaseWeapon->SkeletalMeshComponent->CreateAndSetMaterialInstanceDynamic(0);
	const auto MaterialInstace2 = WeaponComponent->BaseWeapon->SkeletalMeshComponent->CreateAndSetMaterialInstanceDynamic(1);
	if (!MaterialInstace1 || !MaterialInstace2)
		return;

	MaterialInstace1->SetVectorParameterValue(PaintColorName, Color);
	MaterialInstace1->SetVectorParameterValue(MasterColorName, Color);
	MaterialInstace2->SetVectorParameterValue(PaintColorName, Color);
	MaterialInstace2->SetVectorParameterValue(MasterColorName, Color);
}
