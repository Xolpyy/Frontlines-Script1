// Frontlines Game, All Rights Reserved

#include "UI/FLHUD.h"
#include "Blueprint/UserWidget.h"
#include "Engine/Canvas.h"
#include "Engine/World.h"

void AFLHUD::BeginPlay()
{
    Super::BeginPlay();

    const auto PlayerWidget = CreateWidget<UUserWidget>(GetWorld(), PlayerWidgetClass);
    if(PlayerWidget)
    {
        PlayerWidget->AddToViewport();
    }
}

void AFLHUD::DrawHUD()
{
    Super::DrawHUD();

    // DrawCrosshair();
}

void AFLHUD::DrawCrosshair()
{
    int32 SizeX = Canvas->SizeX;
    int32 SizeY = Canvas->SizeY;

    TInterval<float> Center(SizeX * 0.5f, SizeY * 0.5f);

    DrawLine(Center.Min - CrosshairLength, Center.Max, Center.Min + CrosshairLength, Center.Max, CrosshairColor, CrosshairThickness);
    DrawLine(Center.Min, Center.Max - CrosshairLength, Center.Min, Center.Max + CrosshairLength, CrosshairColor, CrosshairThickness);
}