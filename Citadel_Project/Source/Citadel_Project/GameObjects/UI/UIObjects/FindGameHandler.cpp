#include "FindGameHandler.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/WidgetComponent.h"
#include "Custom/Events/EventDispatcher.h"
#include "GameObjects/Network/NetworkHandler.h"
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

    SubcribeOnEvents();
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
        widget->SetMessageText(FText::FromString("Server is down..."));
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
        widget->SetMessageText(FText::FromString("Connected... Waiting for players..."));
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
        widget->SetMessageText(FText::FromString("All are ready!"));
    }
}

void AFindGameHandler::OnPlayersNotReady(const EventData& eventData)
{
    if (eventData.eventType != EventType::PlayersNotReady)
    {
        return;
    }

    if (UFindGameWidget* widget = static_cast<UFindGameWidget*>(m_widgetComponent->GetUserWidgetObject()))
    {
        widget->SetMessageText(FText::FromString("Players are not ready..."));
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
        {EventType::PlayersNotReady, [this](const EventData& eventData) { OnPlayersNotReady(eventData); }},
        });
}

void AFindGameHandler::BeginPlay()
{
	Super::BeginPlay();

    GetWorld()->SpawnActor<ANetworkHandler>();
}

void AFindGameHandler::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

