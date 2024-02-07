// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "RedemptionGameMode.generated.h"

class AAudioManager;

UCLASS(minimalapi)
class ARedemptionGameMode : public AGameModeBase
{
	GENERATED_BODY()

private:
	AAudioManager* MyAudioManager;
	bool SafeMusic = true;

public:
	TArray<class AEnemyCharacter*> Enemies;
	ARedemptionGameMode();
	virtual void Tick(float DeltaTime) override;
	virtual void BeginPlay();
	enum class EGameState
	{
		Safe,
		InCombat
	};
	void HandleGameStateChange(EGameState NewState);

};