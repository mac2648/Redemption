// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_DefineNextStandingPoint.generated.h"

class ARedemptionPlayer;
class APatrolPathIndicator;
/**
 * 
 */
UCLASS()
class REDEMPTION_API UBTTask_DefineNextStandingPoint : public UBTTaskNode
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere)
	FBlackboardKeySelector Player;

	UPROPERTY(EditAnywhere)
	FBlackboardKeySelector StandingIndex;

	UPROPERTY(EditAnywhere)
	FBlackboardKeySelector NextPosition;

public:
	UBTTask_DefineNextStandingPoint();

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	APatrolPathIndicator* ClosestPositionToPlayer(ARedemptionPlayer* PlayerChar, TArray<APatrolPathIndicator*>* StandingPoints);
	APatrolPathIndicator*  SecondClosestPositionToPlayer(ARedemptionPlayer* PlayerChar, TArray<APatrolPathIndicator*>* StandingPoints);
};
