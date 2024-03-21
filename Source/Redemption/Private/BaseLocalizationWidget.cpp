// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseLocalizationWidget.h"
#include "Internationalization/Internationalization.h"
#include "Internationalization/Culture.h"
#include "Components/TextBlock.h"


void UBaseLocalizationWidget::NativeConstruct()
{
	Super::NativeConstruct();

	SetFontPerLanguage();
}

void UBaseLocalizationWidget::SetFontPerLanguage()
{
	FString CurrentLanguage = FInternationalization::Get().GetCurrentCulture()->GetName();
	UE_LOG(LogTemp, Warning, TEXT("%s"), *CurrentLanguage);
}
