// Frontlines Game, All Rights Reserved

#include "GameModes/FLGameModeBase.h"
#include "AIController.h"
#include "Engine/World.h"
#include "Player/FLBaseCharacter.h"
#include "Player/FLPlayerController.h"
#include "Player/FLPlayerState.h"
#include "Player/FLSpectatorPawn.h"
#include "TimerManager.h"
#include "UI/FLHUD.h"

AFLGameModeBase::AFLGameModeBase()
{
    DefaultPawnClass = AFLBaseCharacter::StaticClass();
    HUDClass = AFLHUD::StaticClass();
    PlayerControllerClass = AFLPlayerController::StaticClass();
    PlayerStateClass = AFLPlayerState::StaticClass();
    SpectatorClass = AFLSpectatorPawn::StaticClass();
}

void AFLGameModeBase::StartPlay()
{
    Super::StartPlay();

    SpawnBots();

    CreateTeams();

    StartRound();
}

void AFLGameModeBase::SpawnBots()
{
    if (GameData.PlayersAmount < 0)
        return;

    for (int32 i = 0; i < GameData.PlayersAmount - 1; ++i)
    {
        FActorSpawnParameters SpawnParam;
        SpawnParam.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

        const auto AIController = GetWorld()->SpawnActor<AAIController>(AIControllerClass, SpawnParam);

        RestartPlayer(AIController);
    }
}

UClass *AFLGameModeBase::GetDefaultPawnClassForController_Implementation(AController *InController)
{
    if (InController && InController->IsA<AAIController>())
    {
        return AIPawnClass;
    }

    return Super::GetDefaultPawnClassForController_Implementation(InController);
    ;
}

void AFLGameModeBase::StartRound()
{
    RoundCountdown = GameData.RoundTime;
    GetWorld()->GetTimerManager().SetTimer(GameTimerHandle, this, &AFLGameModeBase::UpdateGameTimer, 1.f, true);
}

void AFLGameModeBase::UpdateGameTimer()
{
    if (--RoundCountdown == 0)
    {
        GetWorld()->GetTimerManager().ClearTimer(GameTimerHandle);

        if (Round + 1 <= GameData.RoundsNum)
        {
            ++Round;
            ResetPlayers();
            StartRound();
        }
        else
        {
            GameOver();
        }
    }
}

void AFLGameModeBase::GameOver()
{
    ResetPlayers();
}

void AFLGameModeBase::ResetPlayers()
{
    if (!GetWorld())
        return;

    for (auto It = GetWorld()->GetControllerIterator(); It; ++It)
    {
        ResetOnePlayer(It->Get());
    }
}

void AFLGameModeBase::ResetOnePlayer(AController *Controller)
{
    if (Controller && Controller->GetPawn())
    {
        Controller->GetPawn()->Reset();
    }

    RestartPlayer(Controller);
    SetPlayerColor(Controller);
}

void AFLGameModeBase::CreateTeams()
{
    if (!GetWorld())
        return;

    int32 TeamIndex = 1;
    for (auto It = GetWorld()->GetControllerIterator(); It; ++It)
    {
        const auto Controller = It->Get();
        if (!Controller)
            continue;

        const auto PlayerState = Cast<AFLPlayerState>(Controller->PlayerState);
        if (!PlayerState)
            continue;

        PlayerState->SetTeamIndex(TeamIndex);
        PlayerState->SetTeamColor(DetermineColorByTeamIndex(TeamIndex));
        PlayerState->SetPlayerName(Controller->IsPlayerController() ? TEXT("Player") : GetBotName());

        SetPlayerColor(Controller);

        TeamIndex = TeamIndex == 1 ? 2 : 1;
    }
}
FLinearColor AFLGameModeBase::DetermineColorByTeamIndex(int32 Index) const
{
    if (Index - 1 < GameData.TeamColors.Num())
    {
        return GameData.TeamColors[Index - 1];
    }

    return GameData.DefaultColor;
}

void AFLGameModeBase::SetPlayerColor(AController *Controller)
{
    if (!Controller)
        return;

    const auto PlayerState = Cast<AFLPlayerState>(Controller->PlayerState);
    if (!PlayerState)
        return;

    const auto Pawn = Cast<AFLBaseCharacter>(Controller->GetPawn());
    if (!Pawn)
        return;

    Pawn->SetPlayerColor(PlayerState->GetTeamColor());
    Pawn->SetWeaponColor(PlayerState->GetTeamColor());
}

FString AFLGameModeBase::GetBotName() const
{
    if (!GetWorld())
        return TEXT("Bot");

    int32 Index = 0;
    for (auto It = GetWorld()->GetControllerIterator(); It; ++It)
    {
        ++Index;
        FString BotName = TEXT("Bot ") + FString::FromInt(Index);
        return BotName;
    }

    return TEXT("Bot");
}
