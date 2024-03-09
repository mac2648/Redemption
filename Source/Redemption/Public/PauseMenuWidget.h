// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PauseMenuWidget.generated.h"
class UButton;
/**
 * 
 */
UCLASS()
class REDEMPTION_API UPauseMenuWidget : public UUserWidget
{
	GENERATED_BODY()

protected:

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UButton* ResumeButton;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UButton* ExitButton;

public:
	virtual void NativeConstruct() override;

protected:

	UFUNCTION(BlueprintCallable)
	void Resume();

	UFUNCTION(BlueprintCallable)
	void Exit();
	
};
