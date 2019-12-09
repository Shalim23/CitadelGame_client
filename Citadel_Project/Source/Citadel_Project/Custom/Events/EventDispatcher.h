#pragma once
#include <unordered_map>
#include "Custom/Singleton.h"
#include "Events.h"

class EventDispatcher : public Singleton<EventDispatcher>
{
    using Super = Singleton;

public:
    EventDispatcher();

    std::vector<EventDelegateHandle> subscribe(const std::vector<EventSubscribeData>& callbacks);

    void unsubscribe(const std::vector<EventDelegateHandle>& callbacksData);

    void Reset();

    BaseGameEvent* GetEvent(const EventType& eventType);

private:
    std::unordered_map<EventType, std::unique_ptr<BaseGameEvent>> m_Events;
};
