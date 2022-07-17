// Frontlines Game, All Rights Reserved

#include "AI/FLAIController.h"
#include "AI/FLAICharacter.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Components/FLAIPerceptionComponent.h"

AFLAIController::AFLAIController()
{
    bWantsPlayerState = true;
    
    FLAIPerceptionComponent = CreateDefaultSubobject<UFLAIPerceptionComponent>(TEXT("FLAIPerceptionComponent"));
    SetPerceptionComponent(*FLAIPerceptionComponent);
}

void AFLAIController::OnPossess(APawn *InPawn)
{
    Super::OnPossess(InPawn);

    const auto AICharacter = Cast<AFLAICharacter>(InPawn);
    if (AICharacter && AICharacter->BehaviorTreeComponent)
    {
        RunBehaviorTree(AICharacter->BehaviorTreeComponent);
    }
}

void AFLAIController::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    SetFocus(FLAIPerceptionComponent->GetClosestEnemy());
}

AActor *AFLAIController::GetClosestEnemy() const
{
    return Cast<AActor>(GetBlackboardComponent()->GetValueAsObject(EnemyActorName));
}
