// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenuWidget.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "RedemptionGameInstance.h"
#include "Kismet/KismetSystemLibrary.h"

void UMainMenuWidget::Quit()
{

	//make the functionality for quiting the level
	UKismetSystemLibrary::QuitGame(GetWorld(), nullptr, EQuitPreference::Quit, false);

}



void UMainMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();

	QuitButton->OnClicked.AddDynamic(this, &UMainMenuWidget::Quit);
	OptionsButton->OnClicked.AddDynamic(this, &UMainMenuWidget::Option);

	APlayerController* Controller =  UGameplayStatics::GetPlayerController(GetWorld(), 0);
	Controller->SetInputMode(FInputModeUIOnly());
	Controller->SetShowMouseCursor(true);
	
	Cast<URedemptionGameInstance>(GetGameInstance())->LoadGame();
}
