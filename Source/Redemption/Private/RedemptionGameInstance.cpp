// Fill out your copyright notice in the Description page of Project Settings.


#include "RedemptionGameInstance.h"

FVector URedemptionGameInstance::GetPlayerDiedLocation()
{
	
	return PlayerDiedLocation;
	
}

void URedemptionGameInstance::SetPlayerDiedLocation()
{
	ACharacter* myCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	PlayerDiedLocation = myCharacter->GetActorLocation();
}

void URedemptionGameInstance::TransferInfoSaveToInstance()
{
	PlayerDiedLocation = SaveInfo.PlayerDiedLocation;
	UE_LOG(LogTemp, Warning, TEXT("%s"), *SaveInfo.PlayerDiedLocation.ToString());

	SFXValue = SaveInfo.SFXValue;
	MusicValue = SaveInfo.MusicValue;
}

void URedemptionGameInstance::SetupSaveInfo()
{
	SaveInfo.PlayerDiedLocation = PlayerDiedLocation;
	SaveInfo.SFXValue = SFXValue;
	SaveInfo.MusicValue = MusicValue;
}