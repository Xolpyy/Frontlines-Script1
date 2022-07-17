// Frontlines Game, All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "FLBaseCharacter.generated.h"

class UCameraComponent;
class UFLHealthComponent;
class UFLWeaponComponent;
class USpringArmComponent;
class UTextRenderComponent;

UCLASS()
class FRONTLINES_API AFLBaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AFLBaseCharacter(const FObjectInitializer &ObjectInit);

	UFUNCTION(BlueprintPure)
	bool IsRunning() const;

	// Components
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UFLHealthComponent *HealthComponent = nullptr;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent *PlayerInputComponent) override;

	void SetPlayerColor(const FLinearColor &Color);
	void SetWeaponColor(const FLinearColor &Color);

private:
	// Components
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	USpringArmComponent *SpringArmComponent = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UCameraComponent *CameraComponent = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UFLWeaponComponent *WeaponComponent = nullptr;

	// Movement
	bool bWantsToRun;
	bool bIsMovingForward;
	bool bIsNotMovingRight;

	void StartRunning();
	void StopRunning();
	void MoveForward(float AxisValue);
	void MoveRight(float AxisValue);
	void LookUp(float AxisValue);
	void LookRight(float AxisValue);
	void LookUpRate(float AxisValue);
	void LookRightRate(float AxisValue);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement", meta = (AllowPrivateAccess = "true"))
	float LookUpRateValue = 70.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement", meta = (AllowPrivateAccess = "true"))
	float LookRightRateValue = 70.f;

	// Damage
	UFUNCTION()
	void OnGroundLanded(const FHitResult &Hit);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Fall Damage", meta = (AllowPrivateAccess = "true"))
	FVector2D LandedDamageVelocity = FVector2D(1200.f, 2000.f);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Fall Damage", meta = (AllowPrivateAccess = "true"))
	FVector2D LandedDamageAmount = FVector2D(20.f, 250.f);

	// Player
	FName PlayerColorName = TEXT("Paint Color");
	FName PaintColorName  = TEXT("MasterPaintColour");
	FName MasterColorName = TEXT("MasterGrimeColour");
};
