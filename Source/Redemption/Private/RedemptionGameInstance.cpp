// Fill out your copyright notice in the Description page of Project Settings.

#include "RedemptionGameInstance.h"
#include "RedemptionPlayer.h"
#include "Kismet/GameplayStatics.h"
#include "RedemptionUtils.h"

URedemptionGameInstance::URedemptionGameInstance()
{
	for (int i = 0; i < NUM_LEVELS; i++)
	{
		PlayerDiedLocation.Add(FVector::ZeroVector);
		CompletedLevels.Add(false);
	}
}

FVector URedemptionGameInstance::GetPlayerDiedLocation(int LevelId)
{
	return PlayerDiedLocation[LevelId];
}

void URedemptionGameInstance::SetPlayerDiedLocation(int LevelId)
{
	ACharacter* myCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	PlayerDiedLocation[LevelId] = myCharacter->GetActorLocation();
}

void URedemptionGameInstance::TransferInfoSaveToInstance()
{
	PlayerDiedLocation = SaveInfo.PlayerDiedLocation;

	SFXValue = SaveInfo.SFXValue;
	MusicValue = SaveInfo.MusicValue;
	Resolution = SaveInfo.Resolution;
	WindowMode = SaveInfo.WindowMode;
	IsVsync = SaveInfo.IsVsync;
	Culture = SaveInfo.Culture;
	CameraShake = SaveInfo.CameraShake;
	CompletedLevels = SaveInfo.CompletedLevels;
}

void URedemptionGameInstance::SetupSaveInfo()
{
	SaveInfo.PlayerDiedLocation = PlayerDiedLocation;
	SaveInfo.SFXValue = SFXValue;
	SaveInfo.MusicValue = MusicValue;
	SaveInfo.Resolution = Resolution;
	SaveInfo.WindowMode = WindowMode;
	SaveInfo.IsVsync = IsVsync;
	SaveInfo.Culture = Culture;
	SaveInfo.CameraShake = CameraShake;
	SaveInfo.CompletedLevels = CompletedLevels;
}

void URedemptionGameInstance::SetCompleteLevel()
{
	CompletedLevels[URedemptionUtils::GetWorldID(GetWorld())] = true;
	SetupSaveInfo();
	SaveGame();
}

#ifdef PLAYTEST_TOOLS
void URedemptionGameInstance::UnlockAllLevels()
{
	for (int i = 0; i < NUM_LEVELS; i++)
	{
		CompletedLevels[i] = true;
	}
	SetupSaveInfo();
	SaveGame();
}
#endif