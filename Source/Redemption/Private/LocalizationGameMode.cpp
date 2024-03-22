// Fill out your copyright notice in the Description page of Project Settings.


#include "LocalizationGameMode.h"
#include "FontManager.h"

void ALocalizationGameMode::BeginPlay()
{
	Super::BeginPlay();

	FontManagerInstance = GetWorld()->SpawnActor<AFontManager>(FontManagerClass);
}
