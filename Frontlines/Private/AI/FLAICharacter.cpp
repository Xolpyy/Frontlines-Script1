// Frontlines Game, All Rights Reserved

#include "AI/FLAICharacter.h"
#include "AI/FLAIController.h"
#include "Components/FLAIWeaponComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

AFLAICharacter::AFLAICharacter(const FObjectInitializer &ObjectInit)
    : Super(ObjectInit.SetDefaultSubobjectClass<UFLAIWeaponComponent>(TEXT("WeaponComponent")))
{
    bUseControllerRotationYaw = false;

    AutoPossessAI = EAutoPossessAI::Disabled;
    AIControllerClass = AFLAICharacter::StaticClass();

    if(GetCharacterMovement())
    {
        GetCharacterMovement()->bUseControllerDesiredRotation = true;
        GetCharacterMovement()->RotationRate = FRotator(0.0f, 450.f, 0.0f);
    }
}
