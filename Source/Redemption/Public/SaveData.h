// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "GenericPlatform/GenericWindow.h"
#include "SaveData.generated.h"


/**
 * 
 */

USTRUCT(BlueprintType)
struct FSaveInfo
{
	GENERATED_BODY();
	
	UPROPERTY(BlueprintReadWrite)
	FVector PlayerDiedLocation = FVector::ZeroVector;

	UPROPERTY(BlueprintReadWrite)
	float SFXValue;

	UPROPERTY(BlueprintReadWrite)
	float MusicValue;

	UPROPERTY(BlueprintReadWrite)
	FIntPoint Resolution;

	UPROPERTY(BlueprintReadWrite)
	TEnumAsByte<EWindowMode::Type> WindowMode;
};

UCLASS()
class REDEMPTION_API USaveData : public USaveGame
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite)
	FSaveInfo SaveDataStruct;
};
