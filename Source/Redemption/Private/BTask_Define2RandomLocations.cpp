// Fill out your copyright notice in the Description page of Project Settings.

#include "BTask_Define2RandomLocations.h"
#include "NavigationSystem.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"

const float MAX_DISTANCE = 1000000;

UBTask_Define2RandomLocations::UBTask_Define2RandomLocations()
{
	NodeName = "Define 2 Random Locations";
}

EBTNodeResult::Type UBTask_Define2RandomLocations::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	FVector RandomLocations[3] = {};

	for (int i = 0; i < 3; i++)
	{
		RandomLocations[i] = CreateRandomLocation(OwnerComp);
	}

	AActor* Player = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	float ClosestToPlayer = MAX_DISTANCE;
	int ClosestIndex = -1;

	for (int i = 0; i < 3; i++)
	{
		if (FVector::Dist(Player->GetActorLocation(), RandomLocations[i]) < ClosestToPlayer)
		{
			ClosestIndex = i;
			ClosestToPlayer = FVector::Dist(Player->GetActorLocation(), RandomLocations[i]);
		}
	}

	RandomLocations[ClosestIndex] = FVector::ZeroVector;

	TArray<FVector> NewLocations;

	for (int i = 0; i < 3; i++)
	{
		if (RandomLocations[i] != FVector::ZeroVector)
		{
			NewLocations.Add(RandomLocations[i]);
		}
	}

	OwnerComp.GetBlackboardComponent()->SetValueAsVector(RandomLocation1.SelectedKeyName, NewLocations[0]);
	OwnerComp.GetBlackboardComponent()->SetValueAsVector(RandomLocation2.SelectedKeyName, NewLocations[1]);

	return EBTNodeResult::Succeeded;
}

//creates a random location in the navmesh based on radius
FNavLocation UBTask_Define2RandomLocations::CreateRandomLocation(UBehaviorTreeComponent& OwnerComp)
{
	FNavLocation NewLocation;

	if (UNavigationSystemV1* NavSys = FNavigationSystem::GetCurrent<UNavigationSystemV1>(GetWorld()))
	{
		if (ANavigationData* UseNavData = NavSys->GetDefaultNavDataInstance(FNavigationSystem::DontCreate))
		{
			FVector Location = OwnerComp.GetAIOwner()->GetPawn()->GetActorLocation();
			NavSys->GetRandomReachablePointInRadius(Location, Radius, NewLocation, UseNavData);
		}
	}

	return NewLocation;
}