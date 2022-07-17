// Frontlines Game, All Rights Reserved

#include "Animations/FLBaseAnimNotify.h"
#include "Components/SkeletalMeshComponent.h"

void UFLBaseAnimNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
    Super::Notify(MeshComp, Animation, EventReference);

    OnNotified.Broadcast(MeshComp);
}
