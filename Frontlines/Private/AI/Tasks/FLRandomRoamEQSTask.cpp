// Frontlines Game, All Rights Reserved

#include "AI/Tasks/FLRandomRoamEQSTask.h"
#include "Engine/World.h"
#include "EnvironmentQuery/EnvQueryInstanceBlueprintWrapper.h"
#include "EnvironmentQuery/EnvQueryManager.h"

UFLRandomRoamEQSTask::UFLRandomRoamEQSTask()
{
    NodeName = TEXT("Random Roam EQS");
}

EBTNodeResult::Type UFLRandomRoamEQSTask::ExecuteTask(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory)
{
    Super::ExecuteTask(OwnerComp, NodeMemory);

    QueryInstance = UEnvQueryManager::RunEQSQuery(GetWorld(), nullptr, this, EEnvQueryRunMode::RandomBest5Pct, nullptr);
    if (ensure(QueryInstance))
    {
        // QueryInstance->GetOnQueryFinishedEvent().AddDynamic(this, &UFLRandomRoamEQSTask::OnBotSpawnQueryCompleted);
    }

    return EBTNodeResult::Succeeded;
}

void UFLRandomRoamEQSTask::OnBotSpawnQueryCompleted()
{
    TArray<FVector> Locations = QueryInstance->GetResultsAsLocations();
    int32 Location = FMath::RandRange(0, Locations.Num() - 1);
}
