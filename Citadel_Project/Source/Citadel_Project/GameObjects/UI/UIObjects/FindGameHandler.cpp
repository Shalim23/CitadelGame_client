#include "FindGameHandler.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/WidgetComponent.h"
#include "Custom/Events/EventDispatcher.h"
#include "GameObjects/UI/Widgets/FindGameWidget.h"

AFindGameHandler::AFindGameHandler()
{
 	PrimaryActorTick.bCanEverTick = false;

    m_widgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("FindGameWidget"));
    ConstructorHelpers::FClassFinder<UUserWidget> widget(TEXT("/Game/FindGameWidget"));
    if (widget.Succeeded())
    {
        m_widgetComponent->SetWidgetClass(widget.Class);
    }
}

void AFindGameHandler::OnReturnToMainMenu(const EventData& eventData)
{
    if (eventData.eventType == EventType::ReturnToMainMenu)
    {
        m_EventsHandler.unsubscribe();
        Destroy();
    }
}

void AFindGameHandler::OnNoServerConnection(const EventData& eventData)
{
    if (eventData.eventType != EventType::NoServerConnection)
    {
        return;
    }

    if (UFindGameWidget* widget = static_cast<UFindGameWidget*>(m_widgetComponent->GetUserWidgetObject()))
    {
        widget->SetMessageText("Server is down...");
    }
}

void AFindGameHandler::OnConnectedToServer(const EventData& eventData)
{
    if (eventData.eventType != EventType::ConnectedToServer)
    {
        return;
    }

    if (UFindGameWidget* widget = static_cast<UFindGameWidget*>(m_widgetComponent->GetUserWidgetObject()))
    {
        widget->SetMessageText("Connected... Waiting for players...");
    }
}

void AFindGameHandler::OnGameFound(const EventData& eventData)
{
    if (eventData.eventType != EventType::GameFound)
    {
        return;
    }

    if (UFindGameWidget* widget = static_cast<UFindGameWidget*>(m_widgetComponent->GetUserWidgetObject()))
    {
        widget->OnGameFound();
    }
}

void AFindGameHandler::OnAllPlayersReady(const EventData& eventData)
{
    if (eventData.eventType != EventType::AllPlayersReady)
    {
        return;
    }

    //#TODO implement further game flow!!!
    if (UFindGameWidget* widget = static_cast<UFindGameWidget*>(m_widgetComponent->GetUserWidgetObject()))
    {
        widget->SetMessageText("All is ready!");
    }
}

void AFindGameHandler::OnWaitingForPlayers(const EventData& eventData)
{
    if (eventData.eventType != EventType::WaitingForPlayers)
    {
        return;
    }

    if (UFindGameWidget* widget = static_cast<UFindGameWidget*>(m_widgetComponent->GetUserWidgetObject()))
    {
        widget->OnWaitingForPlayers();
    }
}

void AFindGameHandler::OnNotReady(const EventData& eventData)
{
    if (eventData.eventType != EventType::NotReady)
    {
        return;
    }

    if (UFindGameWidget* widget = static_cast<UFindGameWidget*>(m_widgetComponent->GetUserWidgetObject()))
    {
        widget->OnNotReady();
    }
}

void AFindGameHandler::SubcribeOnEvents()
{
    m_EventsHandler.subscribe({
        {EventType::ReturnToMainMenu, [this](const EventData& eventData) { OnReturnToMainMenu(eventData); }},
        {EventType::NoServerConnection, [this](const EventData& eventData) { OnNoServerConnection(eventData); }},
        {EventType::ConnectedToServer, [this](const EventData& eventData) { OnConnectedToServer(eventData); }},
        {EventType::GameFound, [this](const EventData& eventData) { OnGameFound(eventData); }},
        {EventType::AllPlayersReady, [this](const EventData& eventData) { OnAllPlayersReady(eventData); }},
        {EventType::NotReady, [this](const EventData& eventData) { OnNotReady(eventData); }},
        {EventType::WaitingForPlayers, [this](const EventData& eventData) { OnWaitingForPlayers(eventData); }},
        });
}

void AFindGameHandler::BeginPlay()
{
	Super::BeginPlay();

    SubcribeOnEvents();
}

void AFindGameHandler::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

