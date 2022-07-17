// Frontlines Game, All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "FLCoreTypes.h"
#include "FLBaseAnimNotify.generated.h"

class USkeletalMeshComponent;

/**
 *
 */
UCLASS()
class FRONTLINES_API UFLBaseAnimNotify : public UAnimNotify
{
	GENERATED_BODY()

public:
	FOnNotifiedSignature OnNotified;

	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;
};
