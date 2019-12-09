#pragma once
#include "Custom/Singleton.h"


class IdGenerator : public Singleton<IdGenerator>
{
    using Super = Singleton;

public:

    IdGenerator();

	int generateEventSubscriptionId();
    void Reset();

private:

	int m_eventSubscriptionIdGenerator;

};
