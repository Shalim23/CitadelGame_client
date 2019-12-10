// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Custom/Events/EventsHandler.h"
#include "GameRulesHandler.generated.h"

class UWidgetComponent;
struct EventData;

UCLASS()
class CITADEL_PROJECT_API AGameRulesHandler : public AActor
{
	GENERATED_BODY()
	
public:
    AGameRulesHandler();
    void Tick(float DeltaTime) override;

protected:
    void BeginPlay() override;

private:
    void SubcribeOnEvents();

    void OnReturnToMainMenu(const EventData& eventData);

private:
    UPROPERTY()
    UWidgetComponent* m_widget;

    EventsHandler m_EventsHandler;

};
