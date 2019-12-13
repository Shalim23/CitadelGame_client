#pragma once
#include "Containers/UnrealString.h"
#include "Serialization/MemoryReader.h"

//messages from server
static const char* WaitingForPlayersMessage = "WaitingForPlayers";
static const char* WaitingForReadinessMessage = "WaitingForReadiness";
static const char* AllAreReadyMessage = "AllAreReady";
static const char* NotReadyMessage = "NotReady";

//messages from client
static const char* IsReadyMessage = "IsReady";
static const char* ClientCancelMessage = "ClientCancel";


struct MessageFromServer
{
    MessageFromServer(const TArray<uint8>& rawData)
        : messageName()
        , data(rawData, true)
    {
        data << messageName;
    }
    
    FString messageName;
    FMemoryReader data;
};