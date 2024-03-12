// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "RedemptionPlayer.h"
#include "SaveData.h"
#include "Kismet/GameplayStatics.h"
#include "RedemptionGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class REDEMPTION_API URedemptionGameInstance : public UGameInstance
{
	GENERATED_BODY()

protected:
	
	FVector PlayerDiedLocation = FVector::ZeroVector;

	UPROPERTY(BlueprintReadWrite)
	FSaveInfo SaveInfo;


public:

	FVector GetPlayerDiedLocation();
	void SetPlayerDiedLocation();

	UFUNCTION(BlueprintImplementableEvent)
	void SaveGame();

	UFUNCTION(BlueprintImplementableEvent)
	void LoadGame();
};
