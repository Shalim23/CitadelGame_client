#pragma once
#include <functional>

class NetworkMessagesHandler
{
public:
    void Init();

    void ProcessMessage(const FString& message, const FMemoryReader& data);

private:
    void OnNetAllAreReadyMessage(const FMemoryReader& data);
    void OnNetWaitingForReadinessMessage(const FMemoryReader& data);
    void OnNetWaitingForPlayersMessage(const FMemoryReader& data);

private:
    TMap<FString, std::function<void(const FMemoryReader&)>> m_NetEventsCallbacks;
};