#include "NetworkMessagesHandler.h"
#include "NetworkEventsStrings.h"
#include "Custom/Events/EventDispatcher.h"

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
    if (BaseGameEvent* playersNotReadyEvent = EventDispatcher::GetInstance().GetEvent(EventType::PlayersNotReady))
    {
        playersNotReadyEvent->Broadcast(PlayersNotReadyEventData());
    }
}

void NetworkMessagesHandler::OnNetAllAreReadyMessage(const FMemoryReader& data)
{
    if (BaseGameEvent* allPlayersReadyEvent = EventDispatcher::GetInstance().GetEvent(EventType::AllPlayersReady))
    {
        allPlayersReadyEvent->Broadcast(AllPlayersReadyEventData());
    }
}

void NetworkMessagesHandler::OnNetWaitingForReadinessMessage(const FMemoryReader& data)
{
    if (BaseGameEvent* gameFoundEvent = EventDispatcher::GetInstance().GetEvent(EventType::GameFound))
    {
        gameFoundEvent->Broadcast(GameFoundEventData());
    }
}