#include "FindGameHandler.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/WidgetComponent.h"
#include "Custom/Events/EventDispatcher.h"
#include "GameObjects/NetworkHandler.h"
#include "GameObjects/UIObjects/Widgets/FindGameWidget.h"

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

void AFindGameHandler::SubcribeOnEvents()
{
    m_EventsHandler.subscribe({
        {EventType::ReturnToMainMenu, [this](const EventData& eventData) { OnReturnToMainMenu(eventData); }},
        {EventType::NoServerConnection, [this](const EventData& eventData) { OnReturnToMainMenu(eventData); }},
        {EventType::ConnectedToServer, [this](const EventData& eventData) { OnReturnToMainMenu(eventData); }},
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

