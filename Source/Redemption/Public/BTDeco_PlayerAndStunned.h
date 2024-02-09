// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Decorators/BTDecorator_Blackboard.h"
#include "BTDeco_PlayerAndStunned.generated.h"

/**
 * 
 */
UCLASS()
class REDEMPTION_API UBTDeco_PlayerAndStunned : public UBTDecorator_Blackboard
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere)
	FBlackboardKeySelector Player;

	UPROPERTY(EditAnywhere)
	FBlackboardKeySelector IsStuned;

public:
	UBTDeco_PlayerAndStunned();
	
protected:
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
};
