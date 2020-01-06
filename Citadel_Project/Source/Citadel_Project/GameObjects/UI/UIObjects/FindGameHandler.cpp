#include "FindGameHandler.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/WidgetComponent.h"
#include "Custom/Events/EventDispatcher.h"
#include "GameObjects/UI/Widgets/FindGameWidget.h"
#include "GameObjects/Network/NetworkManager.h"

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
    if (eventData.eventType == GameplayEventType::ReturnToMainMenu)
    {
        m_EventsHandler.unsubscribe();
        Destroy();
    }
}

void AFindGameHandler::OnNoServerConnection(const EventData& eventData)
{
    if (eventData.eventType == GameplayEventType::NoServerConnection)
    {
        if (UFindGameWidget* widget = static_cast<UFindGameWidget*>(m_widgetComponent->GetUserWidgetObject()))
        {
            widget->SetMessageText("Server is down...");
        }
    }
    else if (eventData.eventType == GameplayEventType::ServerConnectionLost)
    {
        if (UFindGameWidget* widget = static_cast<UFindGameWidget*>(m_widgetComponent->GetUserWidgetObject()))
        {
            widget->OnConnectionLost();
        }
    }
}

void AFindGameHandler::OnConnectedToServer(const EventData& eventData)
{
    if (eventData.eventType != GameplayEventType::NoServerConnection)
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
    if (eventData.eventType != GameplayEventType::ConnectedToServer)
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
    if (eventData.eventType != GameplayEventType::AllPlayersReady)
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
    if (eventData.eventType != GameplayEventType::WaitingForPlayers)
    {
        return;
    }

    if (UFindGameWidget* widget = static_cast<UFindGameWidget*>(m_widgetComponent->GetUserWidgetObject()))
    {
        widget->OnWaitingForPlayers();
    }
}

void AFindGameHandler::OnWidgetConstructed()
{
    GetWorld()->SpawnActor<ANetworkManager>();
}

void AFindGameHandler::OnNotReady(const EventData& eventData)
{
    if (eventData.eventType != GameplayEventType::NotReady)
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
        {GameplayEventType::ReturnToMainMenu, [this](const EventData& eventData) { OnReturnToMainMenu(eventData); }},
        {GameplayEventType::NoServerConnection, [this](const EventData& eventData) { OnNoServerConnection(eventData); }},
        {GameplayEventType::ConnectedToServer, [this](const EventData& eventData) { OnConnectedToServer(eventData); }},
        {GameplayEventType::GameFound, [this](const EventData& eventData) { OnGameFound(eventData); }},
        {GameplayEventType::AllPlayersReady, [this](const EventData& eventData) { OnAllPlayersReady(eventData); }},
        {GameplayEventType::NotReady, [this](const EventData& eventData) { OnNotReady(eventData); }},
        {GameplayEventType::WaitingForPlayers, [this](const EventData& eventData) { OnWaitingForPlayers(eventData); }},
        {GameplayEventType::ServerConnectionLost, [this](const EventData& eventData) { OnNoServerConnection(eventData); }},
        });
}

void AFindGameHandler::BeginPlay()
{
	Super::BeginPlay();

    SubcribeOnEvents();

    if (UFindGameWidget* widget = static_cast<UFindGameWidget*>(m_widgetComponent->GetUserWidgetObject()))
    {
        widget->SetOnConstructedCallback([this]() { OnWidgetConstructed(); });
    }
}

void AFindGameHandler::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

