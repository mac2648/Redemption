// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "LocalizationGameMode.h"
#include "RedemptionGameMode.generated.h"

class AAudioManager;

UCLASS(minimalapi)
class ARedemptionGameMode : public ALocalizationGameMode
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditDefaultsOnly, category = "DeadBody")
	TSubclassOf<AActor> DeadBodyClass;

private:
	AAudioManager* MyAudioManager;
	bool SafeMusic = true;

public:
	TArray<class ALandEnemyController*> Enemies;
	ARedemptionGameMode();
	virtual void Tick(float DeltaTime) override;
	virtual void BeginPlay();
	enum class EGameState
	{
		Safe,
		InCombat
	};
	void HandleGameStateChange(EGameState NewState);
	void DestroyInteractableActors();

protected:
	UFUNCTION()
	void HandlePlayerSightUpdate();

};