// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "FindGameWidget.generated.h"

class UButton;
class UTextBlock;

UCLASS()
class CITADEL_PROJECT_API UFindGameWidget : public UUserWidget
{
	GENERATED_BODY()

public:
    UFindGameWidget(const FObjectInitializer& objectInitializer);

    void SetMessageText(const FText& text);
    void OnGameFound();

protected:
    UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
    UButton* ToMainMenuButton;

    UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
    UButton* ReadyButton;

    UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
    UTextBlock* MessageText;

private:
    void NativeConstruct() override;

    UFUNCTION()
    void ReturnToMainMenu();

    UFUNCTION()
    void OnReadyButtonPressed();
	
};