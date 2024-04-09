// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseLocalizationWidget.h"
#include "Internationalization/Internationalization.h"
#include "Internationalization/Culture.h"
#include "Components/TextBlock.h"
#include "Engine/Font.h"
#include "LocalizationGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "FontManager.h"
#include "Components/Button.h"
#include "Components/CheckBox.h"
#include "Components/Slider.h"


void UBaseLocalizationWidget::NativeConstruct()
{
	Super::NativeConstruct();

	bIsFocusable = true;
}

UFont* UBaseLocalizationWidget::SetFontPerLanguage() const
{
	FString CurrentLanguage = FInternationalization::Get().GetCurrentCulture()->GetName();
	UE_LOG(LogTemp, Warning, TEXT("%s"), *CurrentLanguage);

	return Cast<ALocalizationGameMode>(UGameplayStatics::GetGameMode(GetWorld()))->GetFontManagerInstance()->GetFonts(CurrentLanguage);
}

void UBaseLocalizationWidget::SetButtonTint(UButton* Button, FSlateColor NewColor)
{
	FButtonStyle Style = Button->GetStyle();
	FSlateBrush NewSlateBrush = Style.Normal;
	NewSlateBrush.TintColor = NewColor;
	Style.SetNormal(NewSlateBrush);
	Button->SetStyle(Style);
}

void UBaseLocalizationWidget::SetCheckBoxTint(class UCheckBox* Box, FSlateColor NewColor)
{
	FCheckBoxStyle NewStyle = Box->WidgetStyle;

	FSlateBrush NewUnchecked = NewStyle.UncheckedImage;
	NewUnchecked.TintColor = NewColor;
	NewStyle.SetUncheckedImage(NewUnchecked);

	FSlateBrush NewChecked = NewStyle.CheckedImage;
	NewChecked.TintColor = NewColor;
	NewStyle.SetCheckedImage(NewChecked);

	Box->SetWidgetStyle(NewStyle);
}

void UBaseLocalizationWidget::SetSliderTint(class USlider* Slider, struct FSlateColor NewColor)
{
	FSliderStyle SliderStyle = Slider->GetWidgetStyle();

	FSlateBrush NormalImage = SliderStyle.NormalBarImage;
	NormalImage.TintColor = NewColor;
	SliderStyle.SetNormalBarImage(NormalImage);

	Slider->SetWidgetStyle(SliderStyle);
}