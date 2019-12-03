#include "NetworkHandler.h"
#include "Networking.h"
#include "Custom/Events/Events.h"


ANetworkHandler::ANetworkHandler()
{
	PrimaryActorTick.bCanEverTick = false;

    m_EventsHandler.subscribe({
        {EventType::FindGame, [this](const EventData& eventData) { OnFindGame(eventData); }},
        });

}

void ANetworkHandler::OnFindGame(const EventData& eventData)
{
    if (eventData.eventType != EventType::FindGame)
    {
        return;
    }

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
        //#TODO process to next game step
    }
    else
    {
        //#TODO spawn UI instance with error
    }
}

void ANetworkHandler::BeginPlay()
{
	Super::BeginPlay();

}

void ANetworkHandler::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    m_Socket->Recv(m_Buffer, m_NetMessageSize, m_BytesRead);
    if (m_BytesRead > 0)
    {
        DeserializeAndSend(TArray<uint8>(m_Buffer, m_BytesRead));
        
        m_BytesRead = 0;
    }
}

void ANetworkHandler::SerializeAndSend(const NetEventData& eventBase)
{
    FBufferArchive toBinary;
    eventBase.Serialize(toBinary);

    const int64 size = toBinary.TotalSize();
    int32 sent = 0;
    m_Socket->Send(toBinary.GetData(), size, sent);

    int error = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->GetLastErrorCode();
    if (error == SE_ECONNRESET)
    {
        //#TODO spawn UI instance with error
    }
}

void ANetworkHandler::DeserializeAndSend(TArray<uint8> data)
{
    FMemoryReader fromBinary(data, true);
    int eventTypeInInt = 0;

    fromBinary << eventTypeInInt;

    //switch (static_cast<NetEventType>(eventTypeInInt))
    //{
    //    default:
    //       break; //#TODO add reqiured cases
    //}
}
