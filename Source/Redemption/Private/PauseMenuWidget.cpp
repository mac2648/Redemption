// Fill out your copyright notice in the Description page of Project Settings.


#include "PauseMenuWidget.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"


void UPauseMenuWidget::Resume()
{
	// Hide the pause menu widget
	SetVisibility(ESlateVisibility::Hidden);

	// Unpause the game
	UGameplayStatics::SetGamePaused(GetWorld(), false);

	// Set input mode back to game
	APlayerController* Controller = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	Controller->SetInputMode(FInputModeGameOnly());
	Controller->bShowMouseCursor = false;
}

void UPauseMenuWidget::Exit()
{
	//Opens the "MainMenu" Map
	UGameplayStatics::OpenLevel(GetWorld(), "MainMenu");

	APlayerController* Controller = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	Controller->SetInputMode(FInputModeGameOnly());
	Controller->bShowMouseCursor = false;

}


void UPauseMenuWidget::NativeConstruct()
{

	ResumeButton->OnClicked.AddDynamic(this, &UPauseMenuWidget::Resume);
	ExitButton->OnClicked.AddDynamic(this, &UPauseMenuWidget::Exit);

	APlayerController* Controller = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	Controller->SetInputMode(FInputModeUIOnly());
	Controller->SetShowMouseCursor(true)

	
}


