#include "NetworkMessagesHandler.h"
#include "NetworkData.h"
#include "Custom/Events/EventDispatcher.h"

void NetworkMessagesHandler::Init()
{
    m_NetEventsCallbacks.Add(WaitingForPlayersMessage,
        [this](const FMemoryReader& data) { OnNetWaitingForPlayersMessage(data); });

    m_NetEventsCallbacks.Add(AllAreReadyMessage,
        [this](const FMemoryReader& data) { OnNetAllAreReadyMessage(data); });

    m_NetEventsCallbacks.Add(WaitingForReadinessMessage,
        [this](const FMemoryReader& data) { OnNetWaitingForReadinessMessage(data); });

    m_NetEventsCallbacks.Add(NotReadyMessage,
        [this](const FMemoryReader& data) { OnNetNotReadyMessage(data); });
}

void NetworkMessagesHandler::ProcessMessage(const FString& message, const FMemoryReader& data)
{
    if (auto callback = m_NetEventsCallbacks.Find(message))
    {
        (*callback)(data);
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

void NetworkMessagesHandler::OnNetWaitingForPlayersMessage(const FMemoryReader& data)
{
    if (BaseGameEvent* waitingForPlayersEvent = EventDispatcher::GetInstance().GetEvent(EventType::WaitingForPlayers))
    {
        waitingForPlayersEvent->Broadcast(WaitingForPlayersEventData());
    }
}

void NetworkMessagesHandler::OnNetNotReadyMessage(const FMemoryReader& data)
{
    if (BaseGameEvent* notReadyEvent = EventDispatcher::GetInstance().GetEvent(EventType::NotReady))
    {
        notReadyEvent->Broadcast(NotReadyEventData());
    }
}