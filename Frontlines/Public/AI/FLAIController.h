// Frontlines Game, All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "FLAIController.generated.h"

class UFLAIPerceptionComponent;

/**
 *
 */
UCLASS()
class FRONTLINES_API AFLAIController : public AAIController
{
	GENERATED_BODY()

public:
	AFLAIController();

	virtual void Tick(float DeltaTime) override;

protected:
	virtual void OnPossess(APawn *InPawn) override;

private:
	AActor *GetClosestEnemy() const;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UFLAIPerceptionComponent *FLAIPerceptionComponent = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Artificial Intelligence", meta = (AllowPrivateAccess = "true"))
	FName EnemyActorName = TEXT("EnemyActor");
};
