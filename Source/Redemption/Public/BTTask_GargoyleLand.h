// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_GargoyleLand.generated.h"

/**
 * 
 */
UCLASS()
class REDEMPTION_API UBTTask_GargoyleLand : public UBTTaskNode
{
	GENERATED_BODY()

protected:

	UPROPERTY(EditAnywhere)
	FBlackboardKeySelector StadingRotation;

	UPROPERTY(EditAnywhere)
	FBlackboardKeySelector LocationIndex;

	UPROPERTY(EditAnywhere)
	FBlackboardKeySelector IsLanded;

	UPROPERTY(EditAnywhere)
	float Speed = 100;

public:
	UBTTask_GargoyleLand();

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	
};
