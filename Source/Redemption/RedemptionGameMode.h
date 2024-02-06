// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "AudioManager.h"
#include "RedemptionGameMode.generated.h"

UCLASS(minimalapi)
class ARedemptionGameMode : public AGameModeBase
{
	GENERATED_BODY()

private:
	AudioManager* MyAudioManager;

public:

	ARedemptionGameMode();
	virtual void BeginPlay();
	enum class EGameState
	{
		Safe,
		InCombat
	};
	void HandleGameStateChange(EGameState NewState);

};