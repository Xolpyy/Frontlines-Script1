// Frontlines Game, All Rights Reserved

#include "AI/Services/FLFindEnemyService.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Components/FLAIPerceptionComponent.h"

UFLFindEnemyService::UFLFindEnemyService()
{
    NodeName = TEXT("Find Enemy");
}

void UFLFindEnemyService::TickNode(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory, float DeltaSeconds)
{
    Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

    const auto Blackboard = OwnerComp.GetBlackboardComponent();
    if (Blackboard)
    {
        const auto AIController = OwnerComp.GetAIOwner();
        const auto PerceptionComponent = FLUtils::GetCharacterComponent<UFLAIPerceptionComponent>(AIController);
        if (PerceptionComponent)
        {
            Blackboard->SetValueAsObject(EnemyActorKey.SelectedKeyName, PerceptionComponent->GetClosestEnemy());
        }
    }
}
