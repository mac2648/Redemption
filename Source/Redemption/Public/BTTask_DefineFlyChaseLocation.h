// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_DefineFlyChaseLocation.generated.h"

/**
 * 
 */
UCLASS()
class REDEMPTION_API UBTTask_DefineFlyChaseLocation : public UBTTaskNode
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere)
	FBlackboardKeySelector Player;

	UPROPERTY(EditAnywhere)
	FBlackboardKeySelector NextLocation;

	UPROPERTY(EditAnywhere)
	float Height = 300;

	UPROPERTY(EditAnywhere)
	float Speed = 100;

public:
	UBTTask_DefineFlyChaseLocation();

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	
};
