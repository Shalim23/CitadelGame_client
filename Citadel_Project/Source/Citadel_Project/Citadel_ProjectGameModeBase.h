// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Citadel_ProjectGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class CITADEL_PROJECT_API ACitadel_ProjectGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;
};
