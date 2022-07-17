// Frontlines Game, All Rights Reserved

#include "AI/Services/FLFireService.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Components/FLWeaponComponent.h"

UFLFireService::UFLFireService()
{
    NodeName = TEXT("Fire Service");
}

void UFLFireService::TickNode(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory, float DeltaSeconds)
{
    Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

    const auto Blackboard = OwnerComp.GetBlackboardComponent();
    const auto AIController = OwnerComp.GetAIOwner();
    const auto EnemyActor = Blackboard && Blackboard->GetValueAsObject(EnemyActorKey.SelectedKeyName);
    
    if (AIController)
    {
        const auto WeaponComponent = FLUtils::GetCharacterComponent<UFLWeaponComponent>(AIController->GetPawn());
        if (WeaponComponent)
        {
            EnemyActor ? WeaponComponent->StartShooting() : WeaponComponent->StopShooting();
        }
    }
}
