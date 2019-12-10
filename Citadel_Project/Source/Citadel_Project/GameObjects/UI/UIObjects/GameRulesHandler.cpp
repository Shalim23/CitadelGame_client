// Fill out your copyright notice in the Description page of Project Settings.


#include "GameRulesHandler.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/WidgetComponent.h"
#include "Custom/Events/Events.h"

AGameRulesHandler::AGameRulesHandler()
{
    PrimaryActorTick.bCanEverTick = false;
    
    m_widget = CreateDefaultSubobject<UWidgetComponent>(TEXT("GameRulesWidget"));
    ConstructorHelpers::FClassFinder<UUserWidget> widget(TEXT("/Game/GameRulesWidget"));
    if (widget.Succeeded())
    {
        m_widget->SetWidgetClass(widget.Class);
    }
}

void AGameRulesHandler::OnReturnToMainMenu(const EventData& eventData)
{
    if (eventData.eventType != EventType::ReturnToMainMenu)
    {
        return;
    }

    m_EventsHandler.unsubscribe();
    Destroy();
}

void AGameRulesHandler::SubcribeOnEvents()
{
    m_EventsHandler.subscribe({
        {EventType::ReturnToMainMenu, [this](const EventData& eventData) { OnReturnToMainMenu(eventData); }},
        });
}

void AGameRulesHandler::BeginPlay()
{
    Super::BeginPlay();

    SubcribeOnEvents();
}

void AGameRulesHandler::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

}
