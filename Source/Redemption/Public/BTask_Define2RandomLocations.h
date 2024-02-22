// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTask_Define2RandomLocations.generated.h"

/**
 * 
 */
UCLASS()
class REDEMPTION_API UBTask_Define2RandomLocations : public UBTTaskNode
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(EditAnywhere)
	FBlackboardKeySelector RandomLocation1;

	UPROPERTY(EditAnywhere)
	FBlackboardKeySelector RandomLocation2;

	UPROPERTY(EditAnywhere)
	float Radius;

public:
	UBTask_Define2RandomLocations();

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	//creates a random location in the navmesh based on radius
	FNavLocation CreateRandomLocation(UBehaviorTreeComponent& OwnerComp);
};
