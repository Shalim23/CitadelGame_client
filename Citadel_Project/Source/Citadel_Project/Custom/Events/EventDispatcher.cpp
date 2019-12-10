#include "EventDispatcher.h"


EventDispatcher::EventDispatcher()
    : Super()
{
    m_Events.insert({ EventType::LeaveFromMainMenu, std::make_unique<LeaveFromMainMenuEvent>() });
    m_Events.insert({ EventType::ReturnToMainMenu, std::make_unique<ReturnToMainMenuEvent>() });
    m_Events.insert({ EventType::FindGame, std::make_unique<FindGameEvent>() });
    m_Events.insert({ EventType::ReadyForGame, std::make_unique<ReadyForGameEvent>() });
    m_Events.insert({ EventType::NoServerConnection, std::make_unique<NoServerConnectionEvent>() });
    m_Events.insert({ EventType::ConnectedToServer, std::make_unique<ConnectedToServerEvent>() });
    m_Events.insert({ EventType::GameFound, std::make_unique<GameFoundEvent>() });
    m_Events.insert({ EventType::AllPlayersReady, std::make_unique<AllPlayersReadyEvent>() });
    m_Events.insert({ EventType::ServerConnectionLost, std::make_unique<ServerConnectionLostEvent>() });
    m_Events.insert({ EventType::WaitingForPlayers, std::make_unique<WaitingForPlayersEvent>() });
}

BaseGameEvent* EventDispatcher::GetEvent(const EventType& eventType)
{
    auto iter = m_Events.find(eventType);
    if (iter != m_Events.end())
    {
        return iter->second.get();
    }
    
    return nullptr;
}

void EventDispatcher::Reset()
{
    for (auto& _event : m_Events)
    {
        _event.second->Clear();
    }
}

std::vector<EventDelegateHandle> EventDispatcher::subscribe(const std::vector<EventSubscribeData>& callbacks)
{
    std::vector<EventDelegateHandle> toReturn;
    toReturn.reserve(callbacks.size());

    for (const EventSubscribeData& callbackData : callbacks)
    {
        auto iter = m_Events.find(callbackData.eventType);
        if (iter != m_Events.end())
        {
            toReturn.push_back({ callbackData.eventType,
                iter->second->AddLambda(callbackData.callback) });
        }
    }

    return toReturn;
}

void EventDispatcher::unsubscribe(const std::vector<EventDelegateHandle>& callbacksData)
{
    for (const auto& callbackData : callbacksData)
    {
        auto iter = m_Events.find(callbackData.eventType);
        if (iter != m_Events.end())
        {
            iter->second->Remove(callbackData.handle);
        }
    }
}