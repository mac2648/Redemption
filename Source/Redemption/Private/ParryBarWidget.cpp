// Fill out your copyright notice in the Description page of Project Settings.


#include "ParryBarWidget.h"
#include "Components/ProgressBar.h"

void UParryBarWidget::NativeConstruct()
{
	Super::NativeConstruct();
	EnergyBar->SetFillColorAndOpacity(FColor::Green);
}

void UParryBarWidget::SetBarValuePercent(float Value)
{
	EnergyBar->SetPercent(Value);
	
	if (Value <= 0.20)
	{
		EnergyBar->SetFillColorAndOpacity(FColor::Red);
	}
	else
	{
		EnergyBar->SetFillColorAndOpacity(FColor::Green);
	}
}