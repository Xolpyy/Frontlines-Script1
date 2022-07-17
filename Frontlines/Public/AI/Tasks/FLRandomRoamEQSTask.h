// Frontlines Game, All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "FLRandomRoamEQSTask.generated.h"

class UEnvQueryInstanceBlueprintWrapper;

/**
 *
 */
UCLASS()
class FRONTLINES_API UFLRandomRoamEQSTask : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UFLRandomRoamEQSTask();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

private:
	UEnvQueryInstanceBlueprintWrapper *QueryInstance = nullptr;

	UFUNCTION()
	void OnBotSpawnQueryCompleted();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI", meta = (AllowPrivateAccess = "true"))
	FName NextLocationName = TEXT("NextLocation");
};
