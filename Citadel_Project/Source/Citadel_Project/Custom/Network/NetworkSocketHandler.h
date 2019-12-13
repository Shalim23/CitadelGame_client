#pragma once
#include <functional>
#include "NetworkData.h"

class FBufferArchive;
class FSocket;

class NetworkSocketHandler
{

public:
    void SetMessageFromServerCallback(std::function<void(const MessageFromServer&)> callback);
    void SetSendErrorCallback(std::function<void()> callback);
    void Shutdown();

    bool TryConnect();

    void Send(FBufferArchive& data);
    void Receive();

private:
    void ProcessReceivedData(const TArray<uint8>& data);

private:
    FSocket* m_Socket = nullptr;

    const static size_t m_NetMessageSize = 256;
    uint8 m_Buffer[m_NetMessageSize] = {};
    int32 m_BytesRead = 0;

    std::function<void(const MessageFromServer&)> m_MessageFromServerCallback;
    std::function<void()> m_SendErrorCallback;
};
