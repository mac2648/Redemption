// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_DefineNextPatrolPoint.generated.h"

class APatrolPathIndicator;

UCLASS()
class REDEMPTION_API UBTTask_DefineNextPatrolPoint : public UBTTaskNode
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, category = "BTTask Patrol")
	FBlackboardKeySelector PatrolLocation;

	UPROPERTY(EditAnywhere, category = "BTTask Patrol")
	FBlackboardKeySelector WaitTime;

	UPROPERTY(EditAnywhere, category = "BTTask Patrol")
	FBlackboardKeySelector PatrolIndex;

public:
	UBTTask_DefineNextPatrolPoint();

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	bool SetNextPatrolLocation(const TMap<APatrolPathIndicator*, float>* PatrolPath, UBlackboardComponent* BBComp);
};
