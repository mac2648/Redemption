// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_SearchArea.h"
#include "AIController.h"
#include "math.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "EnemyCharacter.h"
#include "PatrolComponent.h"
#include "PatrolPathIndicator.h"

#define GET_PATROL_INDICATOR Get(FSetElementId::FromInteger(OwnerComp.GetBlackboardComponent()->GetValueAsInt(PatrolIndex.SelectedKeyName))).Key

UBTTask_SearchArea::UBTTask_SearchArea()
{
	NodeName = "SearchArea";
}

EBTNodeResult::Type UBTTask_SearchArea::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EnemyChar = Cast<AEnemyCharacter>(OwnerComp.GetAIOwner()->GetCharacter());

	if (IsRandom)
	{
		FRotator RandomRotation = FRotator(0, FMath::RandRange(-180, 180), 0);

		OwnerComp.GetBlackboardComponent()->SetValueAsRotator(GetSelectedBlackboardKey(), RandomRotation);
	}
	else
	{
		if (EnemyChar)
		{
			APatrolPathIndicator* Patrol = EnemyChar->GetPatrolComponent()->GetPatrolPath()->GET_PATROL_INDICATOR;
			OwnerComp.GetBlackboardComponent()->SetValueAsRotator(GetSelectedBlackboardKey(), Patrol->GetActorRotation());
		}
	}
	
	
	if (EnemyChar)
	{
		EnemyChar->SetCharaterRotationRateYaw(90);
		EnemyChar->GetWorldTimerManager().SetTimer(TimeHandler, this, &UBTTask_SearchArea::ResetCharacterRotationRate, 2.0f, false);
	}

	return EBTNodeResult::Succeeded;
}

void UBTTask_SearchArea::ResetCharacterRotationRate()
{
	EnemyChar->SetCharaterRotationRateYaw(300);
}