// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenuWidget.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"

void UMainMenuWidget::Start()
{
	//UE_LOG(LogTemp, Warning, TEXT("START"));
	UGameplayStatics::OpenLevel(GetWorld(), "Prototype_Level1");
	APlayerController* Controller = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	Controller->SetInputMode(FInputModeGameOnly());

}

void UMainMenuWidget::Quit()
{

	//make the functionality for quiting the level
	UKismetSystemLibrary::QuitGame(GetWorld(), nullptr, EQuitPreference::Quit, false);

}


void UMainMenuWidget::NativeConstruct()
{

	StartButton->OnClicked.AddDynamic(this, &UMainMenuWidget::Start);
	QuitButton->OnClicked.AddDynamic(this, &UMainMenuWidget::Quit);

	APlayerController* Controller =  UGameplayStatics::GetPlayerController(GetWorld(), 0);
	Controller->SetInputMode(FInputModeUIOnly());
	Controller->SetShowMouseCursor(true);
	

}
