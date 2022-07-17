// Frontlines Game, All Rights Reserved

#include "Player/FLSpectatorPawn.h"
#include "Blueprint/UserWidget.h"
#include "Camera/CameraComponent.h"
#include "Engine/World.h"

AFLSpectatorPawn::AFLSpectatorPawn()
{
    CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
    CameraComponent->bUsePawnControlRotation = true;
    CameraComponent->SetupAttachment(GetRootComponent());
}

void AFLSpectatorPawn::BeginPlay()
{
    Super::BeginPlay();

    const auto SpectatorWidget = CreateWidget<UUserWidget>(GetWorld(), SpectatorWidgetClass);
    if(SpectatorWidget)
    {
        SpectatorWidget->AddToViewport();
    }
}
