#include "NetworkMessagesHandler.h"
#include "NetworkEventsStrings.h"

NetworkMessagesHandler::NetworkMessagesHandler()
{
    m_NetEventsCallbacks.Add(NotReadyMessage,
        [this](const FMemoryReader& data) { OnNetNotReadyMessage(data); });

    m_NetEventsCallbacks.Add(AllAreReadyMessage,
        [this](const FMemoryReader& data) { OnNetAllAreReadyMessage(data); });

    m_NetEventsCallbacks.Add(WaitingForReadinessMessage,
        [this](const FMemoryReader& data) { OnNetWaitingForReadinessMessage(data); });
}

void NetworkMessagesHandler::ProcessMessage(const FString& message, const FMemoryReader& data)
{
    if (auto callback = m_NetEventsCallbacks.Find(message))
    {
        (*callback)(data);
    }
}

void NetworkMessagesHandler::OnNetNotReadyMessage(const FMemoryReader& data)
{
    //#TODO handle this case
}

void NetworkMessagesHandler::OnNetAllAreReadyMessage(const FMemoryReader& data)
{
    //#TODO handle this case
}

void NetworkMessagesHandler::OnNetWaitingForReadinessMessage(const FMemoryReader& data)
{
    //#TODO handle this case
}