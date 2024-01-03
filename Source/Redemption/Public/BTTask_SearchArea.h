// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_SearchArea.generated.h"

class AEnemyCharacter;
/**
 * 
 */
UCLASS()
class REDEMPTION_API UBTTask_SearchArea : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

protected:
	//if true will set the key to a random value, if false will set the key to the current index point of patrol
	UPROPERTY(EditAnywhere)
	bool IsRandom;

	UPROPERTY(EditAnywhere)
	FBlackboardKeySelector PatrolIndex;

	AEnemyCharacter* EnemyChar;
	FTimerHandle TimeHandler;
	
public:
	UBTTask_SearchArea();

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	void ResetCharacterRotationRate();
};
