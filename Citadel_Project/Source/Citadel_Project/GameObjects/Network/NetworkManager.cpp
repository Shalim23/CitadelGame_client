#include "NetworkManager.h"
#include "Custom/Events/Events.h"
#include "Custom/Events/EventDispatcher.h"
#include "Serialization/BufferArchive.h"


ANetworkManager::ANetworkManager()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ANetworkManager::BeginPlay()
{
	Super::BeginPlay();
    SetActorTickEnabled(false);

    SubscribeOnEvents();

    m_NetworkSocketHandler.SetMessageFromServerCallback(
        [this](const MessageFromServer& message) { ProcessMessage(message); });

    m_NetworkSocketHandler.SetSendErrorCallback(
        [this]() { OnConnectionError(); });

    m_NetworkMessagesHandler.Init();

    Connect();
}

void ANetworkManager::OnReturnToMainMenu(const EventData& eventData)
{
    if (eventData.eventType == EventType::ReturnToMainMenu)
    {
        if (m_IsConnected)
        {
            FBufferArchive toBinary;

            FString clientCancelMessage(ClientCancelMessage);
            toBinary << clientCancelMessage;

            m_NetworkSocketHandler.Send(toBinary);
        }

        Shutdown();
    }
}

void ANetworkManager::OnPlayerReady(const EventData& eventData)
{
    if (eventData.eventType == EventType::ReadyForGame)
    {
        FBufferArchive toBinary;

        FString isReadyMessage(IsReadyMessage);
        toBinary << isReadyMessage;

        m_NetworkSocketHandler.Send(toBinary);
    }
}

void ANetworkManager::Connect()
{
    if (m_NetworkSocketHandler.TryConnect())
    {
        m_IsConnected = true;
        SetActorTickEnabled(true);

        if (BaseGameEvent* connectedToServerEvent = EventDispatcher::GetInstance().GetEvent(EventType::ConnectedToServer))
        {
            connectedToServerEvent->Broadcast(ConnectedToServerEventData());
        }
    }
    else
    {
        if (BaseGameEvent* noServerConnectionEvent = EventDispatcher::GetInstance().GetEvent(EventType::NoServerConnection))
        {
            noServerConnectionEvent->Broadcast(NoServerConnectionEventData());
        }
    }
}

void ANetworkManager::Shutdown()
{
    m_NetworkSocketHandler.Shutdown();
    m_EventsHandler.unsubscribe();
    Destroy();
}

void ANetworkManager::SubscribeOnEvents()
{
    m_EventsHandler.subscribe({
        {EventType::ReturnToMainMenu, [this](const EventData& eventData) { OnReturnToMainMenu(eventData); }},
        {EventType::ReadyForGame, [this](const EventData& eventData) { OnPlayerReady(eventData); }},
        });
}

void ANetworkManager::ProcessMessage(const MessageFromServer& message)
{
    m_NetworkMessagesHandler.ProcessMessage(message.messageName, message.data);
}

void ANetworkManager::OnConnectionError()
{
    if (BaseGameEvent* serverConnectionLostEvent = EventDispatcher::GetInstance().GetEvent(EventType::ServerConnectionLost))
    {
        serverConnectionLostEvent->Broadcast(ServerConnectionLostEventData());
    }

    Shutdown();
}

void ANetworkManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
    m_NetworkSocketHandler.Receive();
}

