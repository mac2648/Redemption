// Fill out your copyright notice in the Description page of Project Settings.

#include "BTTask_Attack.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"
#include "AIController.h"
#include "GameFramework/DamageType.h"
#include "GameFramework/Pawn.h"

UBTTask_Attack::UBTTask_Attack()
{
	NodeName = "Attack";
}

//The function that is called when the task is executed
EBTNodeResult::Type UBTTask_Attack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	APawn* OwnerPawn = OwnerComp.GetAIOwner()->GetPawn();

	FVector AttackPosition = OwnerPawn->GetActorLocation() + OwnerPawn->GetActorForwardVector() * 80;

	OwnerComp.GetBlackboardComponent()->SetValueAsVector(NextLocation.SelectedKeyName, AttackPosition);
	OwnerComp.GetBlackboardComponent()->SetValueAsFloat(WaitTime.SelectedKeyName, StunDuration);
	OwnerComp.GetBlackboardComponent()->SetValueAsBool(IsStuned.SelectedKeyName, true);

	return EBTNodeResult::Succeeded;
}