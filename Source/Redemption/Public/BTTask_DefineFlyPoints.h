// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_DefineFlyPoints.generated.h"

/**
 * 
 */
UCLASS()
class REDEMPTION_API UBTTask_DefineFlyPoints : public UBTTaskNode
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere)
	FBlackboardKeySelector LocationIndex;

	UPROPERTY(EditAnywhere)
	FBlackboardKeySelector PathPoint1;

	UPROPERTY(EditAnywhere)
	FBlackboardKeySelector PathPoint2;


public:
	UBTTask_DefineFlyPoints();

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
