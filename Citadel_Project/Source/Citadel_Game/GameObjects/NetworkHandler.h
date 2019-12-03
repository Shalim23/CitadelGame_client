//This class must have only 1 instance during all game flow
//Must be put on scene in editor from the begining
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Custom/Events/EventsHandler.h"
#include "NetworkHandler.generated.h"

class NetEventData;
struct EventData;

UCLASS()
class CITADEL_GAME_API ANetworkHandler : public AActor
{
	GENERATED_BODY()
	
public:	
	ANetworkHandler();
	void Tick(float DeltaTime) override;

protected:
	void BeginPlay() override;

private:
    void SerializeAndSend(const NetEventData& eventBase);
    void DeserializeAndSend(TArray<uint8> data);

    void OnFindGame(const EventData& eventData);

private:
    FSocket* m_Socket = nullptr;
    EventsHandler m_EventsHandler;
    
    const static size_t m_NetMessageSize = 256;
    uint8 m_Buffer[m_NetMessageSize] = {};
    int32 m_BytesRead = 0;
};
