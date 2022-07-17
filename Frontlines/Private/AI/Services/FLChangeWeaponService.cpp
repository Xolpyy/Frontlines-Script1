// Frontlines Game, All Rights Reserved

#include "AI/Services/FLChangeWeaponService.h"
#include "AIController.h"
#include "Components/FLWeaponComponent.h"

UFLChangeWeaponService::UFLChangeWeaponService()
{
    NodeName = TEXT("Change Weapon");
}

void UFLChangeWeaponService::TickNode(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory, float DeltaSeconds)
{
    Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

    const auto AIController = OwnerComp.GetAIOwner();
    if (AIController)
    {
        const auto WeaponComponent = FLUtils::GetCharacterComponent<UFLWeaponComponent>(AIController->GetPawn());
        if(WeaponComponent && FMath::FRand() < Probability && Probability > 0)
        {
            WeaponComponent->NextWeapon();
        }
    }
}
