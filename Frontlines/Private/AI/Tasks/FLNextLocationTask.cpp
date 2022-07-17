// Frontlines Game, All Rights Reserved

#include "AI/Tasks/FLNextLocationTask.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "NavigationSystem.h"

UFLNextLocationTask::UFLNextLocationTask()
{
    NodeName = TEXT("Next Location");
}

EBTNodeResult::Type UFLNextLocationTask::ExecuteTask(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory)
{
    Super::ExecuteTask(OwnerComp, NodeMemory);

    const auto Blackboard = OwnerComp.GetBlackboardComponent();
    const auto AIController = OwnerComp.GetAIOwner();
    if (!AIController || !Blackboard)
        return EBTNodeResult::Failed;

    const auto AIPawn = AIController->GetPawn();
    if (!AIPawn)
        return EBTNodeResult::Failed;

    const auto NavSys = UNavigationSystemV1::GetCurrent(AIPawn);
    if (!NavSys)
        return EBTNodeResult::Failed;

    FVector TargetLocation = AIPawn->GetActorLocation();
    if (!bSelfCenter)
    {
        const auto EnemyActor = Cast<AActor>(Blackboard->GetValueAsObject(EnemyActorKey.SelectedKeyName));
        if (!EnemyActor)
            return EBTNodeResult::Failed;

        TargetLocation = EnemyActor->GetActorLocation();
    }

    FNavLocation NavLocation;
    const auto Point = NavSys->GetRandomReachablePointInRadius(TargetLocation, Radius, NavLocation);
    if (Point)
    {
        Blackboard->SetValueAsVector(LocationKey.SelectedKeyName, NavLocation.Location);
    }

    return EBTNodeResult::Succeeded;
}
