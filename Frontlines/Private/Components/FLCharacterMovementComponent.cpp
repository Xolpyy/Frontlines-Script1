// Frontlines Game, All Rights Reserved

#include "Components/FLCharacterMovementComponent.h"
#include "GameFramework/Character.h"
#include "Player/FLBaseCharacter.h"

float UFLCharacterMovementComponent::GetMaxSpeed() const
{
    const auto MaxSpeed = Super::GetMaxSpeed();

    const auto Character = Cast<AFLBaseCharacter>(GetOwner());
    
    return Character && Character->IsRunning() ? MaxSpeed * SpeedMulitplier : MaxSpeed;
}
