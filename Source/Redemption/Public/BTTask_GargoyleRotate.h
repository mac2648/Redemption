// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_GargoyleRotate.generated.h"

/**
 * 
 */
UCLASS()
class REDEMPTION_API UBTTask_GargoyleRotate : public UBTTaskNode
{
	GENERATED_BODY()
	
protected:

	UPROPERTY(EditAnywhere)
	FBlackboardKeySelector StandingRotation;

	UPROPERTY(EditAnywhere)
	float RotSpeed = 10;

public:
	UBTTask_GargoyleRotate();

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
