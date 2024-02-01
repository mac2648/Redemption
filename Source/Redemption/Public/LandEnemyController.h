// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RedemptionController.h"
#include "LandEnemyController.generated.h"

class UAISenseConfig_Hearing;
/**
 * 
 */
UCLASS()
class REDEMPTION_API ALandEnemyController : public ARedemptionController
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(VisibleAnywhere, Category = "Sense")
	UAISenseConfig_Hearing* HearingSenseConfig;

public:
	ALandEnemyController();

protected:
	virtual void BeginPlay() override;
	virtual void UpdateTargetPerception(AActor* Actor, FAIStimulus Stimulus) override;

	virtual void UpdateSight(AActor* Actor, FAIStimulus Stimulus) override;
	virtual void UpdateHearing(FAIStimulus Stimulus);
};
