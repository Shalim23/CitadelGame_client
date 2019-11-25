// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Citadel_GameGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class CITADEL_GAME_API ACitadel_GameGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;
	
};
