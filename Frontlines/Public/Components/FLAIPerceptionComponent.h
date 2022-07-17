// Frontlines Game, All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Perception/AIPerceptionComponent.h"
#include "FLUtils.h"
#include "FLAIPerceptionComponent.generated.h"

/**
 *
 */
UCLASS()
class FRONTLINES_API UFLAIPerceptionComponent : public UAIPerceptionComponent
{
	GENERATED_BODY()

public:
	AActor *GetClosestEnemy() const;
};
