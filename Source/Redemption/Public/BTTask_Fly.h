// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_Fly.generated.h"

/**
 * 
 */
UCLASS()
class REDEMPTION_API UBTTask_Fly : public UBTTaskNode
{
	GENERATED_BODY()

protected:

	UPROPERTY(EditAnywhere)
	FBlackboardKeySelector Location;


	UPROPERTY(EditAnywhere)
	FBlackboardKeySelector IsLanded;

	UPROPERTY(EditAnywhere)
	float Speed = 100;

public:
	UBTTask_Fly();

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	
};
