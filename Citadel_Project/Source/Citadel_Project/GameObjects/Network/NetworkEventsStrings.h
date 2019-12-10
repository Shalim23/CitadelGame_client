#pragma once
#include "Containers/UnrealString.h"

//messages from server
static const FString WaitingForReadinessMessage = "WaitingForReadiness";
static const FString AllAreReadyMessage = "AllAreReady";
static const FString NotReadyMessage = "NotReady";

//messages from client
static const FString IsReadyMessage = "IsReady";
static const FString ClientCancelMessage = "ClientCancel";