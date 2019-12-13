// Fill out your copyright notice in the Description page of Project Settings.


#include "CitadelGameInstance.h"
#include "Custom/Singleton/SingletonManager.h"


UCitadelGameInstance::UCitadelGameInstance(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
    SingletonManager::GetInstance().Init();
}

void UCitadelGameInstance::Shutdown()
{
    Super::Shutdown();

    SingletonManager::GetInstance().Shutdown();
}
