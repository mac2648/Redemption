// Fill out your copyright notice in the Description page of Project Settings.


#include "RedemptionUtils.h"

int32 URedemptionUtils::GetWorldID(UWorld* WorldContextObject)
{
	FString MapName = WorldContextObject->GetName();
	MapName.RemoveAt(0, 5);
	//Levels need to be called "Level" + the number
	UE_LOG(LogTemp, Warning, TEXT("Level %d"), FCString::Atoi(*MapName));
	UE_LOG(LogTemp, Warning, TEXT("MapName = %s"), *MapName);
	return FCString::Atoi(*MapName);
}