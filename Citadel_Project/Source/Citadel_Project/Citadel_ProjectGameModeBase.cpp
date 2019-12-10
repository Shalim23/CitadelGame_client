#include "Citadel_ProjectGameModeBase.h"
#include "GameObjects/UI/UIObjects/MainMenuHandler.h"

void ACitadel_ProjectGameModeBase::BeginPlay()
{
    Super::BeginPlay();

    APlayerController* controller = GetWorld()->GetFirstPlayerController();
    if (controller)
    {
        controller->SetInputMode(FInputModeUIOnly());
        controller->bShowMouseCursor = true;
    }

    GetWorld()->SpawnActor<AMainMenuHandler>();
}