#include "NetworkHandler.h"
#include "Networking.h"
#include "Custom/Events/Events.h"
#include "Custom/Events/EventDispatcher.h"
#include "NetworkEventsStrings.h"


ANetworkHandler::ANetworkHandler()
{
    PrimaryActorTick.bCanEverTick = false;
}

void ANetworkHandler::SubscribeOnEvents()
{
    m_EventsHandler.subscribe({
        {EventType::ReturnToMainMenu, [this](const EventData& eventData) { OnReturnToMainMenu(eventData); }},
        {EventType::ReadyForGame, [this](const EventData& eventData) { OnPlayerReady(eventData); }},
        });
}

void ANetworkHandler::OnPlayerReady(const EventData& eventData)
{
    if (eventData.eventType == EventType::ReadyForGame)
    {
        FBufferArchive toBinary;

        FText isReadyMessage = FText::FromString(IsReadyMessage);
        toBinary << isReadyMessage;

        Send(toBinary);
    }
}

void ANetworkHandler::OnReturnToMainMenu(const EventData& eventData)
{
    if (eventData.eventType == EventType::ReturnToMainMenu)
    {
        if (m_Socket->GetConnectionState() == SCS_Connected)
        {
            FBufferArchive toBinary;
        
            FText clientCancelMessage = FText::FromString(ClientCancelMessage);
            toBinary << clientCancelMessage;

            Send(toBinary);
        }

        m_Socket->Close();

        m_EventsHandler.unsubscribe();
        Destroy();
    }
}

void ANetworkHandler::Connect()
{
    m_Socket = FTcpSocketBuilder("default").AsNonBlocking();

    FIPv4Address ip(127, 0, 0, 1);
    TSharedRef<FInternetAddr> Addr =
        ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateInternetAddr();
    Addr->SetIp(ip.Value);
    Addr->SetPort(56000);

    m_Socket->Connect(*Addr);
    if (m_Socket->GetConnectionState() == SCS_Connected)
    {
        PrimaryActorTick.bCanEverTick = true;

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

void ANetworkHandler::Init()
{
    m_NetworkMessagesHandler.Init();
    SubscribeOnEvents();
    Connect();
}

void ANetworkHandler::BeginPlay()
{
    Super::BeginPlay();

    Init();
}

void ANetworkHandler::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    m_Socket->Recv(m_Buffer, m_NetMessageSize, m_BytesRead);
    if (m_BytesRead > 0)
    {
        Deserialize(TArray<uint8>(m_Buffer, m_BytesRead));

        m_BytesRead = 0;
    }
}

void ANetworkHandler::Send(FBufferArchive& data)
{
    int32 sent = 0;
    m_Socket->Send(data.GetData(), data.TotalSize(), sent);

    int error = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->GetLastErrorCode();
    if (error == SE_ECONNRESET)
    {
        if (BaseGameEvent* serverConnectionLostEvent = EventDispatcher::GetInstance().GetEvent(EventType::ServerConnectionLost))
        {
            serverConnectionLostEvent->Broadcast(ServerConnectionLostEventData());
            //#TODO shutdown network handler
        }
    }
}

void ANetworkHandler::Deserialize(const TArray<uint8>& data)
{
    FMemoryReader fromBinary(data, true);
    FText eventName;

    fromBinary << eventName;

    m_NetworkMessagesHandler.ProcessMessage(eventName.ToString(), fromBinary);
}