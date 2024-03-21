// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Interface_Localization.h"
#include "BaseLocalizationWidget.generated.h"

/**
 * 
 */
UCLASS()
class REDEMPTION_API UBaseLocalizationWidget : public UUserWidget, public IInterface_Localization
{
	GENERATED_BODY()
	
public:

	

public:

	virtual void NativeConstruct() override;

	virtual void SetFontPerLanguage();
};
