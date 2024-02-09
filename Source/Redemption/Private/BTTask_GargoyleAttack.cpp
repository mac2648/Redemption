// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_GargoyleAttack.h"

#include "BTTask_Fly.h"
#include "Gargoyle.h"
#include "PatrolPathIndicator.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/FloatingPawnMovement.h"

#define GET_GARGOYLE Cast<AGargoyle>(OwnerComp.GetAIOwner()->GetPawn())
#define GET_BLACKBOARD OwnerComp.GetBlackboardComponent()

UBTTask_GargoyleAttack::UBTTask_GargoyleAttack()
{
	NodeName = "Gargoyle Attack";
}

EBTNodeResult::Type UBTTask_GargoyleAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AGargoyle* Gargoyle = GET_GARGOYLE;
	FVector CurrentLocation = Gargoyle->GetActorLocation();

	FVector PlayerLocation = Cast<AActor>(GET_BLACKBOARD->GetValueAsObject(Player.SelectedKeyName))->GetActorLocation();

	FVector FlyVec = PlayerLocation - CurrentLocation + FVector(0.0, 0.0, 160.0);
	FlyVec.Normalize();

	UFloatingPawnMovement* GargoyleMoveComp = Gargoyle->GetFloatMovementComp();

	GargoyleMoveComp->Velocity = FlyVec * Speed;

	if ((CurrentLocation - PlayerLocation).Length() < 15.0f)
	{
		GET_BLACKBOARD->ClearValue(Player.SelectedKeyName);
	}

	return EBTNodeResult::Succeeded;
}