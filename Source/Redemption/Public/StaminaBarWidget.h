// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ParryBarWidget.h"
#include "StaminaBarWidget.generated.h"

/**
 * 
 */
UCLASS()
class REDEMPTION_API UStaminaBarWidget : public UParryBarWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere)
	FColor FullStamina;

	UPROPERTY(EditAnywhere)
	FColor LowStamina;

public:
	virtual void NativeConstruct() override;
	void SetBarValuePercent(float const value) override;

};
