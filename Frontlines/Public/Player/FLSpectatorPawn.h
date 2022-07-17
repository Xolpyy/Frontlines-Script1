// Frontlines Game, All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SpectatorPawn.h"
#include "FLSpectatorPawn.generated.h"

class UCameraComponent;
class UUserWidget;

/**
 *
 */
UCLASS()
class FRONTLINES_API AFLSpectatorPawn : public ASpectatorPawn
{
	GENERATED_BODY()

public:
	AFLSpectatorPawn();

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UCameraComponent *CameraComponent = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Health", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UUserWidget> SpectatorWidgetClass;
};
