// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "NetworkHandler.generated.h"

class NetEventData;


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

private:
    FSocket* m_Socket;
    
    const static size_t m_NetMessageSize = 256;
    uint8 m_Buffer[m_NetMessageSize] = {};
    int32 m_BytesRead = 0;
};
