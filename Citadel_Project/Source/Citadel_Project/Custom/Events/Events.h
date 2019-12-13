#pragma once
#include <functional>

class FBufferArchive;
class FMemoryReader;

enum class EventType
{
    Base,
    LeaveFromMainMenu,
    ReturnToMainMenu,
    FindGame,
    ReadyForGame,
    NoServerConnection,
    ConnectedToServer,
    GameFound,
    AllPlayersReady,
    NotReady,
    ServerConnectionLost,
    WaitingForPlayers,
};

struct EventData
{
    EventType eventType;

public:
    virtual void Serialize(FBufferArchive& data) {}
    virtual void Deserialize(FMemoryReader& data) {}

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
DECLARE_DERIVED_EVENT(EventDispatcher, BaseGameEvent, GameFoundEvent)
DECLARE_DERIVED_EVENT(EventDispatcher, BaseGameEvent, AllPlayersReadyEvent)
DECLARE_DERIVED_EVENT(EventDispatcher, BaseGameEvent, NotReadyEvent)
DECLARE_DERIVED_EVENT(EventDispatcher, BaseGameEvent, ServerConnectionLostEvent)
DECLARE_DERIVED_EVENT(EventDispatcher, BaseGameEvent, WaitingForPlayersEvent)

//Client events data

struct NotReadyEventData : public EventData
{
    using Super = EventData;

    NotReadyEventData()
        : Super(EventType::NotReady)
    {}
};

struct WaitingForPlayersEventData : public EventData
{
    using Super = EventData;

    WaitingForPlayersEventData()
        : Super(EventType::WaitingForPlayers)
    {}
};

struct ServerConnectionLostEventData : public EventData
{
    using Super = EventData;

    ServerConnectionLostEventData()
        : Super(EventType::ServerConnectionLost)
    {}
};

struct AllPlayersReadyEventData : public EventData
{
    using Super = EventData;

    AllPlayersReadyEventData()
        : Super(EventType::AllPlayersReady)
    {}
};

struct GameFoundEventData : public EventData
{
    using Super = EventData;

    GameFoundEventData()
        : Super(EventType::GameFound)
    {}
};

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

struct ReadyForGameEventData : public EventData
{
    using Super = EventData;

    ReadyForGameEventData()
        : Super(EventType::ReadyForGame)
    {}
};
