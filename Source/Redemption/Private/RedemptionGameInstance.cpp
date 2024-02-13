// Fill out your copyright notice in the Description page of Project Settings.


#include "RedemptionGameInstance.h"

void URedemptionGameInstance::GetPlayerDiedLocation(FVector NewPlayerDiedLocation)
{
	ACharacter* myCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	FVector NewPlayerDiedLocation = myCharacter->GetActorLocation();

	PlayerDiedLocation = NewPlayerDiedLocation;
}

void URedemptionGameInstance::SetPlayerDiedLocation()
{
	return PlayerDiedLocation;
}
