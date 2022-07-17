// Frontlines Game, All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "FLUtils.h"
#include "FLChangeWeaponService.generated.h"

/**
 *
 */
UCLASS()
class FRONTLINES_API UFLChangeWeaponService : public UBTService
{
	GENERATED_BODY()

public:
	UFLChangeWeaponService();

protected:
	virtual void TickNode(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory, float DeltaSeconds) override;

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Service Parameters", meta = (AllowPrivateAccess = "true"))
	float Probability = 0.3f;
};
