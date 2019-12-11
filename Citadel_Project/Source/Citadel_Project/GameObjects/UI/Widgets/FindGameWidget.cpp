#include "FindGameWidget.h"

#include "Components/Button.h"
#include "Components/TextBlock.h"

#include "Custom/Events/EventDispatcher.h"
#include "GameObjects/UI/UIObjects/MainMenuHandler.h"
#include "GameObjects/Network/NetworkHandler.h"

UFindGameWidget::UFindGameWidget(const FObjectInitializer& objectInitializer)
    : Super(objectInitializer)
{}

void UFindGameWidget::NativeConstruct()
{
    Super::NativeConstruct();

    if (ToMainMenuButton)
    {
        ToMainMenuButton->OnPressed.AddDynamic(this, &UFindGameWidget::ReturnToMainMenu);
    }

    if (ReadyButton)
    {
        ReadyButton->OnPressed.AddDynamic(this, &UFindGameWidget::OnReadyButtonPressed);
        
        DeactivateReadyButton();
    }

    SetMessageText("Finding game...");

    AddToViewport();

    GetWorld()->SpawnActor<ANetworkHandler>();
}

void UFindGameWidget::SetMessageText(const char* text) 
{
    if (MessageText)
    {
        MessageText->SetText(FText::FromString(text));
    }
}

void UFindGameWidget::OnGameFound()
{
    if (ReadyButton)
    {
        SetMessageText("Game is found...");

        ReadyButton->SetIsEnabled(true);
        ReadyButton->SetVisibility(ESlateVisibility::Visible);
    }
}

void UFindGameWidget::OnWaitingForPlayers()
{
    if (ReadyButton)
    {
        SetMessageText("Waiting for players...");

        ReadyButton->SetIsEnabled(false);
        ReadyButton->SetVisibility(ESlateVisibility::Hidden);
    }
}

void UFindGameWidget::OnNotReady()
{
    if (ReadyButton)
    {
        SetMessageText("You are not ready...");

        ReadyButton->SetIsEnabled(false);
        ReadyButton->SetVisibility(ESlateVisibility::Hidden);
    }
}

void UFindGameWidget::ReturnToMainMenu()
{
    if (BaseGameEvent* returnToMainMenuEvent =
        EventDispatcher::GetInstance().GetEvent(EventType::ReturnToMainMenu))
    {
        returnToMainMenuEvent->Broadcast(ReturnToMainMenuEventData());

        RemoveFromParent();
        GetWorld()->SpawnActor<AMainMenuHandler>();
    }
}

void UFindGameWidget::OnReadyButtonPressed()
{
    if (BaseGameEvent* readyForGameEvent = EventDispatcher::GetInstance().GetEvent(EventType::ReadyForGame))
    {
        DeactivateReadyButton();
        SetMessageText("Ready... Waiting for players...");
        
        readyForGameEvent->Broadcast(ReadyForGameEventData());
    }
}

void UFindGameWidget::DeactivateReadyButton()
{
    if (ReadyButton)
    {
        ReadyButton->SetIsEnabled(false);
        ReadyButton->SetVisibility(ESlateVisibility::Hidden);
    }
}

