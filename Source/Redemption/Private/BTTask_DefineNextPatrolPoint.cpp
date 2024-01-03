// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_DefineNextPatrolPoint.h"
#include "AIController.h"
#include "Rat.h"
#include "PatrolComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "PatrolPathIndicator.h"

UBTTask_DefineNextPatrolPoint::UBTTask_DefineNextPatrolPoint()
{
	NodeName = "DefineNextPatrol";
}

EBTNodeResult::Type UBTTask_DefineNextPatrolPoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (UPatrolComponent* PatrolComp = Cast<ARat>(OwnerComp.GetAIOwner()->GetPawn())->GetPatrolComponent())
	{
		if (UBlackboardComponent* BBComp = OwnerComp.GetBlackboardComponent())
		{
			if (SetNextPatrolLocation(PatrolComp, BBComp))
			{
				return EBTNodeResult::Succeeded;
			}
		}
	}

	return EBTNodeResult::Failed;
}

bool UBTTask_DefineNextPatrolPoint::SetNextPatrolLocation(UPatrolComponent* PatrolComp, UBlackboardComponent* BBComp)
{
	const TMap<APatrolPathIndicator*, float>* PatrolPath = PatrolComp->GetPatrolPath();

	TArray<APatrolPathIndicator*> PathIndicators;
	PatrolPath->GetKeys(PathIndicators);

	if (PathIndicators.Num() == 0)
	{
		return false;
	}

	int Index = BBComp->GetValueAsInt(PatrolIndex.SelectedKeyName);

	Index += PatrolComp->GetPatrolDirection();

	if (Index >= PathIndicators.Num() || Index < 0)
	{
		if (PatrolComp->GetPatrolType() == EPatrolType::Loop)
		{
			Index = 0;
		}
		else
		{
			PatrolComp->InverseDirection();
			Index += PatrolComp->GetPatrolDirection() * 2;
		}
	}

	BBComp->SetValueAsVector(PatrolLocation.SelectedKeyName, PathIndicators[Index]->GetActorLocation());
	BBComp->SetValueAsFloat(WaitTime.SelectedKeyName, PatrolPath->Get(FSetElementId::FromInteger(Index)).Value);
	BBComp->SetValueAsInt(PatrolIndex.SelectedKeyName, Index);

	return true;
}