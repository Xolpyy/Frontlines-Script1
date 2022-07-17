// Frontlines Game, All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Player/FLBaseCharacter.h"
#include "FLAICharacter.generated.h"

class UBehaviorTree;

/**
 *
 */
UCLASS()
class FRONTLINES_API AFLAICharacter : public AFLBaseCharacter
{
	GENERATED_BODY()

public:
	AFLAICharacter(const FObjectInitializer &ObjectInit);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Artificial Intelligence", meta = (AllowPrivateAccess = "true"))
	UBehaviorTree *BehaviorTreeComponent = nullptr;
};
