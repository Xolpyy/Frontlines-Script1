#pragma once

#include "Player/FLPlayerState.h"

class FLUtils
{
public:
    template <typename T>
    static T *GetCharacterComponent(AActor *Actor)
    {
        if (!Actor)
            return nullptr;

        const auto Component = Actor->GetComponentByClass(T::StaticClass());
        return Cast<T>(Component);
    }

    bool static AreEnemies(AController *Controller1, AController *Controller2)
    {
        if (!Controller1 || !Controller2)
            return false;

        const auto PlayerState1 = Cast<AFLPlayerState>(Controller1->PlayerState);
        const auto PlayerState2 = Cast<AFLPlayerState>(Controller2->PlayerState);

        return PlayerState1 && PlayerState2 && PlayerState1->GetTeamIndex() != PlayerState2->GetTeamIndex();
    }
};