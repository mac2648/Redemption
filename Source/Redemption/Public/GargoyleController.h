// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RedemptionController.h"
#include "GargoyleController.generated.h"

class AGargoyle;
/**
 * 
 */
UCLASS()
class REDEMPTION_API AGargoyleController : public ARedemptionController
{
	GENERATED_BODY()

public:
	AGargoyleController();
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	void SetStandingIndex(AGargoyle* Gargoyle);

	virtual void UpdateSight(AActor* Actor, FAIStimulus Stimulus) override;
};
