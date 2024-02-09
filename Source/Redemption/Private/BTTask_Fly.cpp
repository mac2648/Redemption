// Fill out your copyright notice in the Description page of Project Settings.

#include "BTTask_Fly.h"
#include "Gargoyle.h"
#include "PatrolPathIndicator.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/FloatingPawnMovement.h"

#define GET_GARGOYLE Cast<AGargoyle>(OwnerComp.GetAIOwner()->GetPawn())
#define GET_BLACKBOARD OwnerComp.GetBlackboardComponent()

UBTTask_Fly::UBTTask_Fly()
{
	NodeName = "Fly";
}

EBTNodeResult::Type UBTTask_Fly::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AGargoyle* Gargoyle = GET_GARGOYLE;
	FVector CurrentLocation = Gargoyle->GetActorLocation();

	FVector LocationVec = GET_BLACKBOARD->GetValueAsVector(Location.SelectedKeyName);
	
	FVector FlyVec = LocationVec - CurrentLocation;
	FlyVec.Normalize();

	UFloatingPawnMovement* GargoyleMoveComp = Gargoyle->GetFloatMovementComp();

	GargoyleMoveComp->Velocity = FlyVec * Speed;

	GET_BLACKBOARD->SetValueAsBool(IsLanded.SelectedKeyName, false);

	if ((CurrentLocation - LocationVec).Length() < 15.0f)
	{
		GET_BLACKBOARD->ClearValue(Location.SelectedKeyName);
	}

	return EBTNodeResult::Succeeded;
}