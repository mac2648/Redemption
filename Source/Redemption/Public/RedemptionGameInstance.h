// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "DevTools.h"
#include "SaveData.h"
#include "RedemptionGameInstance.generated.h"


/**
 * 
 */
UCLASS()
class REDEMPTION_API URedemptionGameInstance : public UGameInstance
{
	GENERATED_BODY()

protected:
	
	TArray<FVector> PlayerDiedLocation;
	TArray<bool> CompletedLevels;

	UPROPERTY(BlueprintReadWrite)
	FSaveInfo SaveInfo;

	float SFXValue;
	float MusicValue;

	FIntPoint Resolution;

	EWindowMode::Type WindowMode;

	FString Culture;

	bool IsVsync;
	bool CameraShake;

	float CameraSensitivity;

public:
	URedemptionGameInstance();

	FVector GetPlayerDiedLocation(int LevelId);
	void SetPlayerDiedLocation(int LevelId);

	UFUNCTION(BlueprintImplementableEvent)
	void SaveGame();

	UFUNCTION(BlueprintImplementableEvent)
	void LoadGame();

	UFUNCTION(BlueprintCallable)
	void TransferInfoSaveToInstance();

	UFUNCTION(BlueprintCallable)
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
	bool GetVsync() const { return IsVsync; }

	UFUNCTION(BlueprintCallable)
	FString GetCulture() const { return Culture; }

	UFUNCTION(BlueprintCallable)
	bool GetCameraShake() const { return CameraShake; }

	UFUNCTION(BlueprintCallable)
	void SetSFXValue(float NewSFXValue) { SFXValue = NewSFXValue; }

	UFUNCTION(BlueprintCallable)
	void SetMusicValue(float NewMusicValue) { MusicValue = NewMusicValue; }

	UFUNCTION(BlueprintCallable)
	void SetResolution(FIntPoint NewResolution) { Resolution = NewResolution; }

	UFUNCTION(BlueprintCallable)
	void SetWindowMode(EWindowMode::Type NewWindowMode) { WindowMode = NewWindowMode; }

	UFUNCTION(BlueprintCallable)
	void SetVsync(bool NewIsVsync) { IsVsync = NewIsVsync; }

	UFUNCTION(BlueprintCallable)
	void SetCulture(FString NewCulture) { Culture = NewCulture; }

	UFUNCTION(BlueprintCallable)
	void SetCameraShake(bool NewCameraShake) { CameraShake = NewCameraShake; }

	UFUNCTION(BlueprintCallable)
	void SetCompleteLevel();

	UFUNCTION(BlueprintCallable)
	bool GetCompletedLevel(int Index) const { return CompletedLevels[Index]; }

	UFUNCTION(BlueprintCallable)
	float GetCameraSensitivity() const { return CameraSensitivity; }

	UFUNCTION(BlueprintCallable)
	void SetCameraSensitivity(float NewCameraSensitivity) { CameraSensitivity = NewCameraSensitivity; }

	void UnlockAllLevels();
};
