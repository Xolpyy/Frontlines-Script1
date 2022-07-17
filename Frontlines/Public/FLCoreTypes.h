#pragma once

#include "FLCoreTypes.generated.h"

class AFLBaseWeapon;
class UNiagaraSystem;
class USkeletalMeshComponent;

// Animations
DECLARE_MULTICAST_DELEGATE_OneParam(FOnNotifiedSignature, USkeletalMeshComponent *);

// Health
DECLARE_MULTICAST_DELEGATE_OneParam(FOnHealthDecreasedSignature, float);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnHealthAddedSignature, float);
DECLARE_MULTICAST_DELEGATE(FOnDeathSignature);

// Weapons
USTRUCT(BlueprintType)
struct FWeaponData
{
    GENERATED_USTRUCT_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Data", meta = (AllowPrivateAccess = "true"))
    TSubclassOf<AFLBaseWeapon> WeaponClass;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Data", meta = (AllowPrivateAccess = "true"))
    UAnimMontage *ReloadAnimMontage = nullptr;
};

USTRUCT(BlueprintType)
struct FAmmoData
{
    GENERATED_USTRUCT_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ammo Data", meta = (AllowPrivateAccess = "true"))
    int32 Bullets;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat", meta = (EditCondition = "!bInfinite"))
    int32 Clips;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat", meta = (AllowPrivateAccess = "true"))
    bool bInfinite;
};

USTRUCT(BlueprintType)
struct FWeaponUIData
{
    GENERATED_USTRUCT_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ammo Data", meta = (AllowPrivateAccess = "true"))
    UTexture2D *CrosshairImage = nullptr;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat", meta = (EditCondition = "!bInfinite"))
    UTexture2D *WeaponIcon = nullptr;
};

DECLARE_MULTICAST_DELEGATE_OneParam(FOnEmptyClipSignature, AFLBaseWeapon *);

// FX
USTRUCT(BlueprintType)
struct FDecalData
{
    GENERATED_USTRUCT_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Decal Data", meta = (AllowPrivateAccess = "true"))
    UMaterialInterface *Material = nullptr;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Decal Data", meta = (AllowPrivateAccess = "true"))
    FVector Size = FVector(10.f);

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Decal Data", meta = (AllowPrivateAccess = "true"))
    float LifeTime = 5.f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Decal Data", meta = (AllowPrivateAccess = "true"))
    float FadeOutTime = 2.f;
};

USTRUCT(BlueprintType)
struct FEffectData
{
    GENERATED_USTRUCT_BODY()
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Impact Data", meta = (AllowPrivateAccess = "true"))
    UNiagaraSystem *DefaultEffect = nullptr;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Impact Data", meta = (AllowPrivateAccess = "true"))
    FDecalData DecalData;
};

// Game Mode
USTRUCT(BlueprintType)
struct FGameData
{
    GENERATED_USTRUCT_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Settings", meta = (AllowPrivateAccess = "true"))
    int32 PlayersAmount = 6.f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Settings", meta = (AllowPrivateAccess = "true"))
    int32 RoundsNum = 3;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Settings", meta = (AllowPrivateAccess = "true"))
    float RoundTime = 10.f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Settings", meta = (AllowPrivateAccess = "true"))
    TArray<FLinearColor> TeamColors;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Settings", meta = (AllowPrivateAccess = "true"))
    FLinearColor DefaultColor = FLinearColor::White;
};
