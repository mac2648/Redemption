// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
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

	FVector GetPlayerDiedLocation(FVector NewPlayerDiedLocation);
	void SetPlayerDiedLocation();
	
};
