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

	float SFXValue;
	float MusicValue;

	FIntPoint Resolution;

	EWindowMode::Type WindowMode;

public:

	FVector GetPlayerDiedLocation();
	void SetPlayerDiedLocation();

	UFUNCTION(BlueprintImplementableEvent)
	void SaveGame();

	UFUNCTION(BlueprintImplementableEvent)
	void LoadGame();

	UFUNCTION(BlueprintCallable)
	void TransferInfoSaveToInstance();

	void SetupSaveInfo();

	UFUNCTION(BlueprintCallable)
	float GetSFXValue() const { return SFXValue; }

	UFUNCTION(BlueprintCallable)
	float GetMusicValue() const { return MusicValue; }

	UFUNCTION(BlueprintCallable)
	FIntPoint GetResolution() const { return Resolution; }

	UFUNCTION(BlueprintCallable)
	EWindowMode::Type GetWindowMode() const { return WindowMode; }

	UFUNCTION(BlueprintCallable)
	void SetSFXValue(float NewSFXValue) { SFXValue = NewSFXValue; }

	UFUNCTION(BlueprintCallable)
	void SetMusicValue(float NewMusicValue) { MusicValue = NewMusicValue; }

	UFUNCTION(BlueprintCallable)
	void SetResolution(FIntPoint NewResolution) { Resolution = NewResolution; }

	UFUNCTION(BlueprintCallable)
	void SetWindowMode(EWindowMode::Type NewWindowMode) { WindowMode = NewWindowMode; }


};
