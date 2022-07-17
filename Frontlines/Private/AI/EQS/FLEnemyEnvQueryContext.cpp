// Frontlines Game, All Rights Reserved

#include "AI/EQS/FLEnemyEnvQueryContext.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "EnvironmentQuery/EnvQueryTypes.h"
#include "EnvironmentQuery/Items/EnvQueryItemType_Actor.h"

void UFLEnemyEnvQueryContext::ProvideContext(FEnvQueryInstance &QueryInstance, FEnvQueryContextData &ContextData) const
{
    Super::ProvideContext(QueryInstance, ContextData);

    const auto QueryOwner = Cast<AActor>(QueryInstance.Owner.Get());

    const auto Blackboard = UAIBlueprintHelperLibrary::GetBlackboard(QueryOwner);
    const auto Enemy = Cast<AActor>(Blackboard->GetValueAsObject(EnemyActorName));

    UEnvQueryItemType_Actor::SetContextHelper(ContextData, Enemy);
}
