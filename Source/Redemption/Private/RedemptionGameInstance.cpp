// Fill out your copyright notice in the Description page of Project Settings.


#include "RedemptionGameInstance.h"

FVector URedemptionGameInstance::GetPlayerDiedLocation()
{
	
	return PlayerDiedLocation;
	
}

void URedemptionGameInstance::SetPlayerDiedLocation()
{
	ACharacter* myCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	PlayerDiedLocation = myCharacter->GetActorLocation() - FVector(0, 0, 74);
}
