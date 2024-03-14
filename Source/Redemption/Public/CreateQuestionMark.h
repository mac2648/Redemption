// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "CreateQuestionMark.generated.h"

/**
 * 
 */
UCLASS()
class REDEMPTION_API UCreateQuestionMark : public UBTTaskNode
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere)
	FBlackboardKeySelector SelfActor;

	UPROPERTY(EditAnywhere)
	FBlackboardKeySelector QuestionMarkWidged;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UUserWidget> QuestionMarkWidgetClass;

public:
	UCreateQuestionMark();

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
