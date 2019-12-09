#pragma once
#include <functional>

enum class EventType
{
    Base,
    LeaveFromMainMenu,
    ReturnToMainMenu,
    FindGame,
    ReadyForGame,
    NoServerConnection,
    ConnectedToServer,
};

struct EventData
{
    EventType eventType;

protected:
    EventData(const EventType& otherEventType)
        : eventType(otherEventType)
    {}
};

struct EventSubscribeData
{
    EventSubscribeData(const EventType& otherEventType, const std::function<void(const EventData&)>& otherCallback)
        : eventType(otherEventType)
        , callback(otherCallback)
    {}

    EventType eventType;
    std::function<void(const EventData&)> callback;
};

struct EventDelegateHandle
{
    EventDelegateHandle(const EventType& otherEventType, const FDelegateHandle& otherHandle)
        : eventType(otherEventType)
        , handle(otherHandle)
    {}

    EventType eventType;
    FDelegateHandle handle;
};

DECLARE_EVENT_OneParam(EventDispatcher, BaseGameEvent, const struct EventData&)
DECLARE_DERIVED_EVENT(EventDispatcher, BaseGameEvent, LeaveFromMainMenuEvent)
DECLARE_DERIVED_EVENT(EventDispatcher, BaseGameEvent, ReturnToMainMenuEvent)
DECLARE_DERIVED_EVENT(EventDispatcher, BaseGameEvent, FindGameEvent)
DECLARE_DERIVED_EVENT(EventDispatcher, BaseGameEvent, ReadyForGameEvent)
DECLARE_DERIVED_EVENT(EventDispatcher, BaseGameEvent, NoServerConnectionEvent)
DECLARE_DERIVED_EVENT(EventDispatcher, BaseGameEvent, ConnectedToServerEvent)

//Client events data

struct NoServerConnectionEventData : public EventData
{
    using Super = EventData;

    NoServerConnectionEventData()
        : Super(EventType::NoServerConnection)
    {}
};

struct ConnectedToServerEventData : public EventData
{
    using Super = EventData;

    ConnectedToServerEventData()
        : Super(EventType::ConnectedToServer)
    {}
};

struct LeaveFromMainMenuEventData : public EventData
{
    using Super = EventData;

    LeaveFromMainMenuEventData()
        : Super(EventType::LeaveFromMainMenu)
    {}
};

struct ReturnToMainMenuEventData : public EventData
{
    using Super = EventData;

    ReturnToMainMenuEventData()
        : Super(EventType::ReturnToMainMenu)
    {}
};

struct FindGameEventData : public EventData
{
    using Super = EventData;

    FindGameEventData()
        : Super(EventType::FindGame)
    {}
};

struct ReadyForGameEventtData : public EventData
{
    using Super = EventData;

    ReadyForGameEventtData()
        : Super(EventType::ReadyForGame)
    {}
};
