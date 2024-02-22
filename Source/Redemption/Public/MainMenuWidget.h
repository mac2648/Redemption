// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainMenuWidget.generated.h"
class UButton;

/**
 * 
 */
UCLASS()
class REDEMPTION_API UMainMenuWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(BlueprintReadOnly,meta = (BindWidget))
	UButton* StartButton;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UButton* QuitButton;
	
	UFUNCTION(BlueprintCallable)
	void Start();

	UFUNCTION(BlueprintCallable)
	void Quit();

public:
	virtual void NativeConstruct() override;
};

