#pragma once
#include <functional>

class NetworkMessagesHandler
{
public:
    NetworkMessagesHandler();

    void ProcessMessage(const FString& message, const FMemoryReader& data);

private:
    void OnNetNotReadyMessage(const FMemoryReader& data);
    void OnNetAllAreReadyMessage(const FMemoryReader& data);
    void OnNetWaitingForReadinessMessage(const FMemoryReader& data);

private:
    TMap<FString, std::function<void(const FMemoryReader&)>> m_NetEventsCallbacks;
};