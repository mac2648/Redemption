// Fill out your copyright notice in the Description page of Project Settings.

#include "BTTask_DefineNextStandingPoint.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "RedemptionPlayer.h"
#include "Gargoyle.h"
#include "PatrolPathIndicator.h"

#define GET_PLAYER Cast<ARedemptionPlayer>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(Player.SelectedKeyName))
#define GET_GARGOYLE Cast<AGargoyle>(OwnerComp.GetAIOwner()->GetPawn())

UBTTask_DefineNextStandingPoint::UBTTask_DefineNextStandingPoint()
{
	NodeName = "Define Next Standing Position";
}

EBTNodeResult::Type UBTTask_DefineNextStandingPoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	ARedemptionPlayer* PlayerCharacter = GET_PLAYER;
	if (!PlayerCharacter)
	{
		return EBTNodeResult::Failed;
	}

	AGargoyle* Gargoyle = GET_GARGOYLE;
	if (!Gargoyle)
	{
		return EBTNodeResult::Failed;
	}

	TArray<APatrolPathIndicator*> StandingPoints = Gargoyle->GetStandingPoints();

	APatrolPathIndicator* ClosestPoint = ClosestPositionToPlayer(PlayerCharacter, &StandingPoints);

	int CurrentStandingIndex = OwnerComp.GetBlackboardComponent()->GetValueAsInt(StandingIndex.SelectedKeyName);

	if (Gargoyle->GetStandingIndex(ClosestPoint) == -1)
	{
		return EBTNodeResult::Failed;
	}

	if (Gargoyle->GetStandingIndex(ClosestPoint) == CurrentStandingIndex)
	{
		ClosestPoint = SecondClosestPositionToPlayer(PlayerCharacter, &StandingPoints);
	}

	if (Gargoyle->GetStandingIndex(ClosestPoint) == -1)
	{
		return EBTNodeResult::Failed;
	}

	OwnerComp.GetBlackboardComponent()->SetValueAsInt(StandingIndex.SelectedKeyName, Gargoyle->GetStandingIndex(ClosestPoint));

	return EBTNodeResult::Succeeded;
}

APatrolPathIndicator* UBTTask_DefineNextStandingPoint::ClosestPositionToPlayer(ARedemptionPlayer* PlayerChar, TArray<APatrolPathIndicator*>* StandingPoints)
{
	FVector PlayerLocation = PlayerChar->GetActorLocation();
	float DistanceToPlayer = 1000000;
	APatrolPathIndicator* Closest = nullptr;

	for (APatrolPathIndicator* Current : *StandingPoints)
	{
		if (FVector::Dist(PlayerLocation, Current->GetActorLocation()) < DistanceToPlayer)
		{
			DistanceToPlayer = FVector::Dist(PlayerLocation, Current->GetActorLocation());
			Closest = Current;
		}
	}

	return Closest;
}

APatrolPathIndicator* UBTTask_DefineNextStandingPoint::SecondClosestPositionToPlayer(ARedemptionPlayer* PlayerChar, TArray<APatrolPathIndicator*>* StandingPoints)
{
	FVector PlayerLocation = PlayerChar->GetActorLocation();
	float ClosestDistanceToPlayer = 1000000;
	float SecondDistanceToPlayer = 1000000;
	APatrolPathIndicator* Closest = nullptr;
	APatrolPathIndicator* SecondClosest = nullptr;

	for (APatrolPathIndicator* Current : *StandingPoints)
	{
		if (FVector::Dist(PlayerLocation, Current->GetActorLocation()) < ClosestDistanceToPlayer)
		{
			SecondDistanceToPlayer = ClosestDistanceToPlayer;
			SecondClosest = Closest;

			ClosestDistanceToPlayer = FVector::Dist(PlayerLocation, Current->GetActorLocation());
			Closest = Current;
		}
	}

	return SecondClosest;
}