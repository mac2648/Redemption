// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_Attack.generated.h"

/**
 * 
 */
UCLASS()
class REDEMPTION_API UBTTask_Attack : public UBTTaskNode
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(EditAnywhere)
	FBlackboardKeySelector NextLocation;

	UPROPERTY(EditAnywhere)
	FBlackboardKeySelector WaitTime;

	UPROPERTY(EditAnywhere)
	FBlackboardKeySelector IsStuned;

	UPROPERTY(EditAnywhere)
	FBlackboardKeySelector Player;

	UPROPERTY(EditAnywhere)
	float StunDuration;


public:
	UBTTask_Attack();

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
