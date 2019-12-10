#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Custom/Events/EventsHandler.h"
#include "NetworkMessagesHandler.h"
#include "NetworkHandler.generated.h"

struct EventData;
class FBufferArchive;

UCLASS()
class CITADEL_PROJECT_API ANetworkHandler : public AActor
{
	GENERATED_BODY()
	
public:
    ANetworkHandler();
    void Tick(float DeltaTime) override;

protected:
    void BeginPlay() override;

private:
    void Send(FBufferArchive& data);
    void Deserialize(const TArray<uint8>& data);

    void Connect();
    void OnReturnToMainMenu(const EventData& eventData);

    void SubscribeOnEvents();

private:
    FSocket* m_Socket = nullptr;
    EventsHandler m_EventsHandler;
    NetworkMessagesHandler m_NetworkMessagesHandler;

    const static size_t m_NetMessageSize = 256;
    uint8 m_Buffer[m_NetMessageSize] = {};
    int32 m_BytesRead = 0;

};
