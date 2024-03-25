// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LandEnemyController.h"
#include "RatController.generated.h"

/**
 * 
 */
UCLASS()
class REDEMPTION_API ARatController : public ALandEnemyController
{
	GENERATED_BODY()
private:
	float PlayerSeenTime = 0.0f;
	FTimerHandle ChaseTimer;
protected:
	void StartChase();
	virtual void UpdateSight(AActor* Actor, FAIStimulus Stimulus) override;
};
