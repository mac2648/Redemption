// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "GenericPlatform/GenericWindow.h"
#include "SaveData.generated.h"

#define NUM_LEVELS 4

USTRUCT(BlueprintType)
struct FSaveInfo
{
	GENERATED_BODY();
	
	UPROPERTY(BlueprintReadWrite)
	TArray<FVector> PlayerDiedLocation;

	UPROPERTY(BlueprintReadWrite)
	TArray<bool> CompletedLevels;

	UPROPERTY(BlueprintReadWrite)
	float SFXValue = 1.0f;

	UPROPERTY(BlueprintReadWrite)
	float MusicValue = 1.0f;

	UPROPERTY(BlueprintReadWrite)
	FIntPoint Resolution = FIntPoint(1280, 720);

	UPROPERTY(BlueprintReadWrite)
	TEnumAsByte<EWindowMode::Type> WindowMode;

	UPROPERTY(BlueprintReadWrite)
	bool IsVsync = false;

	UPROPERTY(BlueprintReadWrite)
	bool CameraShake = true;

	UPROPERTY(BlueprintReadWrite)
	FString Culture = "English";

	UPROPERTY(BlueprintReadWrite)
	float CameraSensitivity = 1.0f;

};

UCLASS()
class REDEMPTION_API USaveData : public USaveGame
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite)
	FSaveInfo SaveDataStruct;

public:
	USaveData();
};
