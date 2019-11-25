#include "JsonDataHelper.h"

void JsonDataHelper::InitJsonData()
{
    m_GameRulesDataHelper.InitGameRulesData();
}

void JsonDataHelper::Reset()
{
    m_GameRulesDataHelper = GameRulesDataHelper();
}
