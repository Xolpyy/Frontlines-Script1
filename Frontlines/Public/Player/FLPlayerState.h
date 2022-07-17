// Frontlines Game, All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "FLPlayerState.generated.h"

/**
 *
 */
UCLASS()
class FRONTLINES_API AFLPlayerState : public APlayerState
{
	GENERATED_BODY()

public:
	int32 GetTeamIndex() const { return TeamIndex; }
	void SetTeamIndex(int32 Index) { TeamIndex = Index; }

	FLinearColor GetTeamColor() const { return TeamColor; }
	void SetTeamColor(const FLinearColor &Color) { TeamColor = Color; }

	int32 GetKillsAmount() const { return KillsAmount;}
	void AddKill() { ++KillsAmount; }

	int32 GetDeathsAmount() const { return DeathsAmount; }
	void AddDeath() { ++DeathsAmount; }

private:
	int32 TeamIndex;
	FLinearColor TeamColor;

	int32 KillsAmount = 0;
	int32 DeathsAmount = 0;
};
