#include "IdGenerator.h"
#include <limits>


//decrement because of INT_MAX as initial value
int IdGenerator::generateEventSubscriptionId()
{
	return m_eventSubscriptionIdGenerator--;
}

void IdGenerator::Reset()
{
    m_eventSubscriptionIdGenerator = INT_MAX;
}

IdGenerator::IdGenerator()
	: Super()
	, m_eventSubscriptionIdGenerator(INT_MAX)
{
}
