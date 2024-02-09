// Fill out your copyright notice in the Description page of Project Settings.

#include "BTTask_GargoyleLand.h"
#include "Gargoyle.h"
#include "PatrolPathIndicator.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/FloatingPawnMovement.h"

#define GET_GARGOYLE Cast<AGargoyle>(OwnerComp.GetAIOwner()->GetPawn())
#define GET_BLACKBOARD OwnerComp.GetBlackboardComponent()
#define FLY_DELAY 6.0f

UBTTask_GargoyleLand::UBTTask_GargoyleLand()
{
	NodeName = "Gargoyle Land";
}

EBTNodeResult::Type UBTTask_GargoyleLand::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AGargoyle* Gargoyle = GET_GARGOYLE;
	if (!Gargoyle) return EBTNodeResult::Failed;

	APatrolPathIndicator* LandingPoint = Gargoyle->GetStandingPoint(GET_BLACKBOARD->GetValueAsInt(LocationIndex.SelectedKeyName));
	FVector LandingPosition = LandingPoint->GetActorLocation();

	FVector CurrentPosition = Gargoyle->GetActorLocation();

	FVector LandingDirection = LandingPosition - CurrentPosition;
	LandingDirection.Normalize();

	UFloatingPawnMovement* GargoyleMoveComp = Gargoyle->GetFloatMovementComp();

	GargoyleMoveComp->Velocity = LandingDirection * Speed;

	UE_LOG(LogTemp, Warning, TEXT("distance: %f"), (LandingPosition - CurrentPosition).Length())
	if ((LandingPosition - CurrentPosition).Length() < 120)
	{
		FRotator NewRotation = LandingPoint->GetActorRotation();

		GET_BLACKBOARD->SetValueAsBool(IsLanded.SelectedKeyName, true);
		GET_BLACKBOARD->SetValueAsRotator(StadingRotation.SelectedKeyName, NewRotation);
		GET_BLACKBOARD->SetValueAsFloat(FlyDelay.SelectedKeyName, FLY_DELAY);
	}

	return EBTNodeResult::Succeeded;
}