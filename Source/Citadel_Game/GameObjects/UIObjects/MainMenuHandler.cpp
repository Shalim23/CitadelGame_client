// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenuHandler.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/WidgetComponent.h"
#include "Custom/Events/Events.h"

AMainMenuHandler::AMainMenuHandler()
{
 	PrimaryActorTick.bCanEverTick = false;

    m_widget = CreateDefaultSubobject<UWidgetComponent>(TEXT("MainMenuWidget"));
    ConstructorHelpers::FClassFinder<UUserWidget> widget(TEXT("/Game/MainMenuWidget"));
    if (widget.Succeeded())
    {
        m_widget->SetWidgetClass(widget.Class);
    }

    SubcribeOnEvents();
}

void AMainMenuHandler::SubcribeOnEvents()
{
    m_EventsHandler.subscribe({ 
        {EventType::LeaveFromMainMenu, [this](const EventData& eventData) { OnLeaveMainMenu(eventData); }},
        });
}

void AMainMenuHandler::OnLeaveMainMenu(const EventData& eventData)
{
    if (eventData.eventType != EventType::LeaveFromMainMenu)
    {
        return;
    }
    
    m_EventsHandler.unsubscribe();
    Destroy();
}

void AMainMenuHandler::BeginPlay()
{
	Super::BeginPlay();
	
}

void AMainMenuHandler::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

