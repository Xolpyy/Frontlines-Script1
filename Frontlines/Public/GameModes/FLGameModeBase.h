// Frontlines Game, All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "FLCoreTypes.h"
#include "GameFramework/GameModeBase.h"
#include "FLGameModeBase.generated.h"

class AAIController;

/**
 *
 */
UCLASS()
class FRONTLINES_API AFLGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	AFLGameModeBase();

	virtual void StartPlay() override;
	virtual UClass *GetDefaultPawnClassForController_Implementation(AController *InController) override;

private:
	FTimerHandle GameTimerHandle;
	int32 RoundCountdown = 1;
	int32 Round = 1;

	void SpawnBots();

	void StartRound();
	void UpdateGameTimer();
	void GameOver();

	void ResetPlayers();
	void ResetOnePlayer(AController *Controller);

	void CreateTeams();
	FLinearColor DetermineColorByTeamIndex(int32 Index) const;
	void SetPlayerColor(AController *Controller);
	FString GetBotName() const;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Game Settings", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<AAIController> AIControllerClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Game Settings", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<APawn> AIPawnClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Settings", meta = (AllowPrivateAccess = "true"))
	FGameData GameData;
};
