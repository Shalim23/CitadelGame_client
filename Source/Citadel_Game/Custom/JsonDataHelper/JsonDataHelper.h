#pragma once
#include "Custom/Singleton.h"
#include "Custom/JsonDataHelper/GameRulesDataHelper.h"


class JsonDataHelper : public Singleton<JsonDataHelper>
{
    using Super = Singleton;

public:
    const GameRulesDataHelper& GetGameRulesDataHelper() const { return m_GameRulesDataHelper; }

    void InitJsonData();
    void Reset();

private:
    GameRulesDataHelper m_GameRulesDataHelper;
};
