// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "CitadelGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class CITADEL_GAME_API UCitadelGameInstance : public UGameInstance
{
	GENERATED_BODY()
public:
    UCitadelGameInstance(const FObjectInitializer& ObjectInitializer);
	
};
