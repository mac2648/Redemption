// Fill out your copyright notice in the Description page of Project Settings.

#include "BTTask_DefineFlyPoints.h"
#include "Gargoyle.h"
#include "PatrolPathIndicator.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

#define GET_GARGOYLE Cast<AGargoyle>(OwnerComp.GetAIOwner()->GetPawn())
#define GET_BLACKBOARD OwnerComp.GetBlackboardComponent()

UBTTask_DefineFlyPoints::UBTTask_DefineFlyPoints()
{
	NodeName = "Define fly points";
}


EBTNodeResult::Type UBTTask_DefineFlyPoints::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AGargoyle* Gargoyle = GET_GARGOYLE;

	FVector FlyPoint1 = Gargoyle->GetActorLocation() + FVector(30.0, 0.0, 250.0);
	UE_LOG(LogTemp, Warning, TEXT("Flypoint1: %s"), *FlyPoint1.ToString())

	GET_BLACKBOARD->SetValueAsVector(PathPoint1.SelectedKeyName, FlyPoint1);

	APatrolPathIndicator* NextStandingPoint = Gargoyle->GetStandingPoint(GET_BLACKBOARD->GetValueAsInt(LocationIndex.SelectedKeyName));
	FVector FlyPoint2 = NextStandingPoint->GetActorLocation() + FVector(30.0, 0.0, 250.0);
	UE_LOG(LogTemp, Warning, TEXT("Flypoint2: %s"), *FlyPoint2.ToString())


	GET_BLACKBOARD->SetValueAsVector(PathPoint2.SelectedKeyName, FlyPoint2);
	GET_BLACKBOARD->SetValueAsInt(PathIndex.SelectedKeyName, 0);

	return EBTNodeResult::Succeeded;
}