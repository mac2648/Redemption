// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Decorators/BTDecorator_Blackboard.h"
#include "BTDeco_SoundAndStunned.generated.h"

/**
 * 
 */
UCLASS()
class REDEMPTION_API UBTDeco_SoundAndStunned : public UBTDecorator_Blackboard
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere)
	FBlackboardKeySelector LastSoundLocation;

	UPROPERTY(EditAnywhere)
	FBlackboardKeySelector IsAttacking;

public:
	UBTDeco_SoundAndStunned();

protected:
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
	
};
