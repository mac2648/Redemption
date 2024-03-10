// Fill out your copyright notice in the Description page of Project Settings.


#include "ParryBarWidget.h"
#include "Components/ProgressBar.h"


void UParryBarWidget::NativeConstruct()
{
	Super::NativeConstruct();
	EnergyBar->SetFillColorAndOpacity(FullParry);

	FullParry = FColor(180.0, 93.0, 161.0, 210.0);
	LowParry = FColor(217.0, 91.0, 154.0, 210);
}

void UParryBarWidget::SetBarValuePercent(float Value)
{
	EnergyBar->SetPercent(Value);
	
	if (Value <= 0.20)
	{
		EnergyBar->SetFillColorAndOpacity(LowParry);
	}
	else
	{
		EnergyBar->SetFillColorAndOpacity(FullParry);
	}
}