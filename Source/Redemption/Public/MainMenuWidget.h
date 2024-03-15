// Fill out your copyright notice in the Desc	1♦4ription page of Project Settings.

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

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UButton* OptionsButton;

	
	TSubclassOf<UUserWidget>OptionsMenuClass;




public:
	virtual void NativeConstruct() override;

protected:
	
	UFUNCTION(BlueprintCallable)
	void Start();

	UFUNCTION(BlueprintCallable)
	void Quit();

	UFUNCTION(BlueprintImplementableEvent)
	void Option();
};

