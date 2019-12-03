// Fill out your copyright notice in the Description page of Project Settings.


#include "CitadelGameInstance.h"
#include "Custom/Events/EventDispatcher.h"
#include "Custom/Events/IdGenerator.h"
#include "Custom/JsonDataHelper/JsonDataHelper.h"

UCitadelGameInstance::UCitadelGameInstance(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
#if defined(UE_BUILD_DEVELOPMENT) || defined(UE_BUILD_DEBUG)

    EventDispatcher::GetInstance().Reset();
    IdGenerator::GetInstance().Reset();
    JsonDataHelper::GetInstance().Reset();
#endif

    JsonDataHelper::GetInstance().InitJsonData();
}
