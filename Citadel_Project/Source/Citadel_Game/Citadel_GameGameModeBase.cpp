// Fill out your copyright notice in the Description page of Project Settings.


#include "Citadel_GameGameModeBase.h"

void ACitadel_GameGameModeBase::BeginPlay()
{
    Super::BeginPlay();
    
    APlayerController* controller = GetWorld()->GetFirstPlayerController();
    if (controller)
    {
        controller->SetInputMode(FInputModeUIOnly());
        controller->bShowMouseCursor = true;
    }
}