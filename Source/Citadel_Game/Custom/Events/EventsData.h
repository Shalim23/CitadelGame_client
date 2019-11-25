#pragma once
#include <memory>
#include "Serialization/BufferArchive.h"

enum class EventType
{
    Base,
    LeaveFromMainMenu,
    ReturnToMainMenu,
};

enum class NetEventType
{
    Base,
};

//Client events data

struct EventData
{
    EventType eventType;

protected:
    EventData(const EventType& otherEventType)
        : eventType(otherEventType)
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

//Network events data

class NetEventData
{
public:
    virtual void Serialize(FBufferArchive& toBinary) const = 0;
    virtual std::unique_ptr<EventData> Deserialize(const FMemoryReader& data) = 0;

    NetEventType eventType;

protected:
    NetEventData(const NetEventType& otherEventType)
        : eventType(otherEventType)
    {}
};
