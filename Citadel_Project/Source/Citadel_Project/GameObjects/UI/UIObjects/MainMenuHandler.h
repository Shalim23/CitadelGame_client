// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Custom/Events/EventsHandler.h"
#include "MainMenuHandler.generated.h"

class UWidgetComponent;
struct EventData;

UCLASS()
class CITADEL_PROJECT_API AMainMenuHandler : public AActor
{
	GENERATED_BODY()
	
public:
    AMainMenuHandler();
    void Tick(float DeltaTime) override;

protected:
    void BeginPlay() override;

private:
    void OnLeaveMainMenu(const EventData& eventData);
    void SubcribeOnEvents();

private:
    UPROPERTY()
    UWidgetComponent* m_widget;

    EventsHandler m_EventsHandler;

};
