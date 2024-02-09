// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_FinishStun.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_FinishStun::UBTTask_FinishStun()
{
	NodeName = "Finish Stun";
}

//task execution
EBTNodeResult::Type UBTTask_FinishStun::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	OwnerComp.GetBlackboardComponent()->SetValueAsBool(IsStuned.SelectedKeyName, false);

	return EBTNodeResult::Succeeded;
}