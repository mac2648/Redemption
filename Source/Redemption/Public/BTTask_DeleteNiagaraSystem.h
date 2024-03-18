// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_DeleteNiagaraSystem.generated.h"

/**
 * 
 */
UCLASS()
class REDEMPTION_API UBTTask_DeleteNiagaraSystem : public UBTTaskNode
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere)
	FBlackboardKeySelector Effect;

public:
	UBTTask_DeleteNiagaraSystem();

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
