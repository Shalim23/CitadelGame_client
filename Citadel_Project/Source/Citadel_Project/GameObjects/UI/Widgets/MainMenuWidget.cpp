// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenuWidget.h"
#include "Components/Button.h"
#include "Custom/Events/EventDispatcher.h"
#include "GameObjects/UI/UIObjects/FindGameHandler.h"
#include "GameObjects/UI/UIObjects/GameRulesHandler.h"

UMainMenuWidget::UMainMenuWidget(const FObjectInitializer& objectInitializer)
    : Super(objectInitializer)
{}

void UMainMenuWidget::NativeConstruct()
{
    Super::NativeConstruct();

    if (StartGameButton)
    {
        StartGameButton->OnPressed.AddDynamic(this, &UMainMenuWidget::FindGame);
    }

    if (GameRulesButton)
    {
        GameRulesButton->OnPressed.AddDynamic(this, &UMainMenuWidget::GoToGameRules);
    }

    if (ExitGameButton)
    {
        ExitGameButton->OnPressed.AddDynamic(this, &UMainMenuWidget::ExitGame);
    }

    AddToViewport();
}

void UMainMenuWidget::GoToGameRules()
{
    if (BaseGameEvent* leaveFromMainMenuEvent =
        EventDispatcher::GetInstance().GetEvent(GameplayEventType::LeaveFromMainMenu))
    {
        leaveFromMainMenuEvent->Broadcast(LeaveFromMainMenuEventData());

        RemoveFromParent();
        GetWorld()->SpawnActor<AGameRulesHandler>();
    }
}

void UMainMenuWidget::ExitGame()
{
    FGenericPlatformMisc::RequestExit(false);
}

void UMainMenuWidget::FindGame()
{
    EventDispatcher& eventDispatcherInstance = EventDispatcher::GetInstance();
    BaseGameEvent* findGameEvent = eventDispatcherInstance.GetEvent(GameplayEventType::FindGame);
    BaseGameEvent* leaveFromMainMenuEvent = eventDispatcherInstance.GetEvent(GameplayEventType::LeaveFromMainMenu);

    if (findGameEvent && leaveFromMainMenuEvent)
    {
        RemoveFromParent();
        GetWorld()->SpawnActor<AFindGameHandler>();

        findGameEvent->Broadcast(FindGameEventData());
        leaveFromMainMenuEvent->Broadcast(LeaveFromMainMenuEventData());
    }
}

