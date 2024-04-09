// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Interface_Localization.h"
#include "BaseLocalizationWidget.generated.h"

/**
 * 
 */

class UFont;

UCLASS()
class REDEMPTION_API UBaseLocalizationWidget : public UUserWidget, public IInterface_Localization
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite)
	bool IsOnControllerMode = false;

public:

	virtual void NativeConstruct() override;

	UFUNCTION(BlueprintCallable)
	virtual UFont* SetFontPerLanguage() const;

protected:
	UFUNCTION(BlueprintCallable)
	void SetButtonTint(class UButton* Button, struct FSlateColor NewColor);

	//this function seems to not work I'm not able to find why
	UFUNCTION(BlueprintCallable)
	void SetCheckBoxTint(class UCheckBox* Box, FSlateColor NewColor);

	UFUNCTION(BlueprintCallable)
	void SetSliderTint(class USlider* Slider, struct FSlateColor NewColor);
};
