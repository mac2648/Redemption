// Fill out your copyright notice in the Description page of Project Settings.


#include "PuzzleLever.h"
#include "InteractWidgetComponent.h"

APuzzleLever::APuzzleLever()
{
	InteractComp = CreateDefaultSubobject<UInteractWidgetComponent>(TEXT("Interact Comp"));
}

void APuzzleLever::Activate()
{
	UE_LOG(LogTemp, Warning, TEXT("ACTIVATE!!!!"))
	IsActive = !IsActive;

	OnActivate.Broadcast();
}