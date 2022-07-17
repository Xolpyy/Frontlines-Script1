// Frontlines Game, All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "FLCoreTypes.h"
#include "FLUtils.h"
#include "FLPlayerWidget.generated.h"

class UFLHealthComponent;
class UProgressBar;
class UFLWeaponComponent;

/**
 *
 */
UCLASS()
class FRONTLINES_API UFLPlayerWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintPure)
	bool GetUIData(FWeaponUIData &UIData) const;

	UFUNCTION(BlueprintPure)
	bool GetAmmoData(FAmmoData &AmmoData) const;

	UFUNCTION(BlueprintPure)
	bool IsPlayerSpectating() const;

	UFUNCTION(BlueprintPure)
	bool IsPlayerDead() const;

protected:
	virtual void NativeOnInitialized() override;

	UPROPERTY(meta = (BindWidget))
	UProgressBar *HealthProgressBar = nullptr;

private:
	void SetHealth();
	void OnHealthDecreased(float Health);
	void OnHealthAdded(float Health);

	UFLHealthComponent *GetHealthComponent() const;
	UFLWeaponComponent *GetWeaponComponent() const;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health", meta = (AllowPrivateAccess = "true"))
	float LowHealthPercent = 0.4f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health", meta = (AllowPrivateAccess = "true"))
	FLinearColor GoodColor = FLinearColor::Green;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health", meta = (AllowPrivateAccess = "true"))
	FLinearColor BadColor = FLinearColor::Red;

	UPROPERTY(meta = (BindWidgetAnim), Transient)
	UWidgetAnimation *DamageImageAnimation = nullptr;

};
