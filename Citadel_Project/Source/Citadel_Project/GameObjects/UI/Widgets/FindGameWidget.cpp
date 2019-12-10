#include "FindGameWidget.h"

#include "Components/Button.h"
#include "Components/TextBlock.h"

#include "Custom/Events/EventDispatcher.h"
#include "GameObjects/UI/UIObjects/MainMenuHandler.h"

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

    SetMessageText(FText::FromString("Finding game..."));

    AddToViewport();
}

void UFindGameWidget::OnGameFound()
{
    if (ReadyButton)
    {
        SetMessageText(FText::FromString("Game is found..."));

        ReadyButton->SetIsEnabled(true);
        ReadyButton->SetVisibility(ESlateVisibility::Visible);
    }
}

void UFindGameWidget::SetMessageText(const FText& text)
{
    if (MessageText)
    {
        MessageText->SetText(text);
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
        SetMessageText(FText::FromString("Ready... Waiting for players..."));
        
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

