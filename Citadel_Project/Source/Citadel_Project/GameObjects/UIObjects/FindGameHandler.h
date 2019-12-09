// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Custom/Events/EventsHandler.h"
#include "FindGameHandler.generated.h"

class UWidgetComponent;
struct EventData;

UCLASS()
class CITADEL_PROJECT_API AFindGameHandler : public AActor
{
	GENERATED_BODY()
	
public:	
	AFindGameHandler();
	void Tick(float DeltaTime) override;

protected:
	void BeginPlay() override;

private:
    void OnReturnToMainMenu(const EventData& eventData);
    void OnNoServerConnection(const EventData& eventData);
    void OnConnectedToServer(const EventData& eventData);

    void SubcribeOnEvents();

private:
    UPROPERTY()
    UWidgetComponent* m_widgetComponent;

    EventsHandler m_EventsHandler;
};
