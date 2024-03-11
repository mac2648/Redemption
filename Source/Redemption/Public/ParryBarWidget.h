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

	UPROPERTY(EditAnywhere)
	FColor FullParry;

	UPROPERTY(EditAnywhere)
	FColor LowParry;
	
public:
	virtual void NativeConstruct() override;
	virtual void SetBarValuePercent(float const value);
};
