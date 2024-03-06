// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ParryBarWidget.generated.h"

class UProgressBar;
/**
 * 
 */
UCLASS()
class REDEMPTION_API UParryBarWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UProgressBar* EnergyBar;
	
public:
	virtual void NativeConstruct() override;
	void SetBarValuePercent(float const value);
};
