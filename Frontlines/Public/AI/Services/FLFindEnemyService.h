// Frontlines Game, All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "FLFindEnemyService.generated.h"

/**
 *
 */
UCLASS()
class FRONTLINES_API UFLFindEnemyService : public UBTService
{
	GENERATED_BODY()

public:
	UFLFindEnemyService();

protected:
	virtual void TickNode(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory, float DeltaSeconds) override;

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Service Parameters", meta = (AllowPrivateAccess = "true"))
	FBlackboardKeySelector EnemyActorKey;
};
