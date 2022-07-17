// Frontlines Game, All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "FLNextLocationTask.generated.h"

/**
 *
 */
UCLASS()
class FRONTLINES_API UFLNextLocationTask : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UFLNextLocationTask();
	
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory) override;

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Task Parameters", meta = (AllowPrivateAccess = "true"))
	float Radius = 1000.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Task Parameters", meta = (AllowPrivateAccess = "true"))
	FBlackboardKeySelector LocationKey;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Task Parameters", meta = (AllowPrivateAccess = "true"))
	FBlackboardKeySelector EnemyActorKey;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Task Parameters", meta = (AllowPrivateAccess = "true"))
	bool bSelfCenter = true;
};
