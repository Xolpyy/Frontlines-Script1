// Frontlines Game, All Rights Reserved

#include "Components/FLAIPerceptionComponent.h"
#include "AIController.h"
#include "Components/FLHealthComponent.h"
#include "Perception/AISenseConfig_Sight.h"

AActor *UFLAIPerceptionComponent::GetClosestEnemy() const
{
    TArray<AActor *> PerceivedActors;
    GetCurrentlyPerceivedActors(UAISenseConfig_Sight::StaticClass(), PerceivedActors);

    if (PerceivedActors.Num() == 0)
        return nullptr;

    const auto AIController = Cast<AAIController>(GetOwner());
    if (!AIController)
        return nullptr;

    const auto AIPawn = AIController->GetPawn();
    if (!AIPawn)
        return nullptr;

    AActor *BestActor = nullptr;
    float BestDistance = MAX_FLT;
    for (const auto PerceivedActor : PerceivedActors)
    {
        const auto HealthComponent = FLUtils::GetCharacterComponent<UFLHealthComponent>(PerceivedActor);
        const auto Pawn = Cast<APawn>(PerceivedActor);
        const auto AreEnemies = FLUtils::AreEnemies(AIController, Pawn->Controller);

        if (HealthComponent && !HealthComponent->IsDead() && AreEnemies)
        {
            auto Distance = (AIPawn->GetActorLocation() - PerceivedActor->GetActorLocation()).Size();
            if (Distance < BestDistance)
            {
                BestDistance = Distance;
                BestActor = PerceivedActor;
            }
        }
    }

    return BestActor;
}
