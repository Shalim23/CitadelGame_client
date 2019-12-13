#include "NetworkSocketHandler.h"
#include "Networking.h"


void NetworkSocketHandler::SetMessageFromServerCallback(std::function<void(const MessageFromServer&)> callback)
{
    m_MessageFromServerCallback = callback;
}

void NetworkSocketHandler::SetSendErrorCallback(std::function<void()> callback)
{
    m_SendErrorCallback = callback;
}

void NetworkSocketHandler::Shutdown()
{
    if (m_Socket)
    {
        m_Socket->Close();
        m_Socket = nullptr;
    }
}

void NetworkSocketHandler::Receive()
{
    m_Socket->Recv(m_Buffer, m_NetMessageSize, m_BytesRead);
    if (m_BytesRead > 0)
    {
        ProcessReceivedData(TArray<uint8>(m_Buffer, m_BytesRead));

        m_BytesRead = 0;
    }
}

bool NetworkSocketHandler::TryConnect()
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
        return true;
    }

    Shutdown();

    return false;
}


void NetworkSocketHandler::Send(FBufferArchive& data)
{
    int32 sent = 0;
    m_Socket->Send(data.GetData(), data.TotalSize(), sent);

    int error = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->GetLastErrorCode();
    if (error == SE_ECONNRESET && m_SendErrorCallback)
    {
        m_SendErrorCallback();
    }
}

void NetworkSocketHandler::ProcessReceivedData(const TArray<uint8>& data)
{
    if (m_MessageFromServerCallback)
    {
        m_MessageFromServerCallback(MessageFromServer(data));
    }
}