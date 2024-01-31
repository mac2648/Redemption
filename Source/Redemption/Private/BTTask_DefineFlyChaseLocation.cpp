// Fill out your copyright notice in the Description page of Project Settings.

#include "BTTask_DefineFlyChaseLocation.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "math.h"

#define PLAYER Player.SelectedKeyName
#define NEXT_LOCATION NextLocation.SelectedKeyName

UBTTask_DefineFlyChaseLocation::UBTTask_DefineFlyChaseLocation()
{
	NodeName = "Flyingchase";
}

EBTNodeResult::Type UBTTask_DefineFlyChaseLocation::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	/*
	UBlackboardComponent* BBComp = OwnerComp.GetBlackboardComponent();
	if (!BBComp) return EBTNodeResult::Failed;

	APawn* PlayerPawn = Cast<APawn>(BBComp->GetValueAsObject(PLAYER));
	if(!PlayerPawn) return EBTNodeResult::Failed;

	ACrow* Crow = Cast<ACrow>(OwnerComp.GetAIOwner()->GetPawn());
	if(!Crow) return EBTNodeResult::Failed;

	FVector PlayerPos = PlayerPawn->GetActorLocation();
	FVector CrowPos = Crow->GetActorLocation();

	FVector Target = PlayerPos - CrowPos;
	Target.Z += Height;

	BBComp->SetValueAsVector(NEXT_LOCATION, Target);

	Target.Normalize();

	UFloatingPawnMovement* CrowMovement = Crow->GetfloatingPawnMovementComp();
	CrowMovement->Velocity = Target * Speed;

	FRotator LookingAngle = Target.Rotation();

	Crow->SetActorRotation(LookingAngle);
	*/
	return EBTNodeResult::Succeeded;
	
}