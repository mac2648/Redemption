// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "RedemptionController.generated.h"

/**
 * 
 */
UCLASS()
class REDEMPTION_API ARedemptionController : public AAIController
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(EditAnywhere, Category = "Behavior")
	UBehaviorTree* Tree;

	UPROPERTY(VisibleAnywhere, Category = "Sense")
	UAIPerceptionComponent* PerceptionComp;

public:
	ARedemptionController();

	UAIPerceptionComponent* GetPerceptionComponent() { return PerceptionComp; }
};
