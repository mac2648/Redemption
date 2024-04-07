// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTask_ZombieAttack.generated.h"

/**
 * 
 */
UCLASS()
class REDEMPTION_API UBTask_ZombieAttack : public UBTTaskNode
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere)
	FBlackboardKeySelector IsAttacking;

	UPROPERTY(EditAnywhere)
	FBlackboardKeySelector IsStunned;

public:
	UBTask_ZombieAttack();

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
