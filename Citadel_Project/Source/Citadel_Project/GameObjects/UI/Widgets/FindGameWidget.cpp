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
        
        ReadyButton->SetIsEnabled(false);
        ReadyButton->SetVisibility(ESlateVisibility::Hidden);
    }

    if (MessageText)
    {
        MessageText->SetText(FText::FromString("Finding game..."));
    }

    AddToViewport();
}

void UFindGameWidget::OnGameFound()
{
    if (MessageText && ReadyButton)
    {
        MessageText->SetText(FText::FromString("Game is found..."));

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
    //#TODO send ready message to server and deactivate button
}

