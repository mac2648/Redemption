// Fill out your copyright notice in the Description page of Project Settings.

#include "BTTask_GargoyleRotate.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

#define GET_BLACKBOARD OwnerComp.GetBlackboardComponent()

UBTTask_GargoyleRotate::UBTTask_GargoyleRotate()
{
	NodeName = "Gargoyle Rotate";
}

EBTNodeResult::Type UBTTask_GargoyleRotate::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	APawn* Pawn = OwnerComp.GetAIOwner()->GetPawn();
	if (!Pawn) return EBTNodeResult::Failed;

	FRotator DesiredRotation = GET_BLACKBOARD->GetValueAsRotator(StadingRotation.SelectedKeyName);

	FRotator NewRotation = FMath::Lerp(Pawn->GetActorRotation(), DesiredRotation, RotSpeed);

	Pawn->SetActorRotation(NewRotation);

	if ((NewRotation - DesiredRotation).IsNearlyZero(0.001))
	{
		GET_BLACKBOARD->ClearValue(StadingRotation.SelectedKeyName);
	}

	return EBTNodeResult::Succeeded;
}