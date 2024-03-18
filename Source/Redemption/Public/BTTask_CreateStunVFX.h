// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_CreateStunVFX.generated.h"

/**
 * 
 */
UCLASS()
class REDEMPTION_API UBTTask_CreateStunVFX : public UBTTaskNode
{
	GENERATED_BODY()
protected:
	UPROPERTY(EditAnywhere)
	class UNiagaraSystem* Effect;

	UPROPERTY(EditAnywhere)
	FBlackboardKeySelector SelfActor;

	UPROPERTY(EditAnywhere)
	FBlackboardKeySelector StunEffect;
	
public:
	UBTTask_CreateStunVFX();

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
