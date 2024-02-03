// Fill out your copyright notice in the Description page of Project Settings.

#include "GargoyleController.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Gargoyle.h"
#include "PatrolPathIndicator.h"
#include "BehaviorTree/BlackboardComponent.h"

#define GET_GARGOYLE Cast<AGargoyle>(GetOwner())

const int PERIPHERAL_VISION_ANGLE = 60;
const int SIGHT_RADIUS = 3000;

AGargoyleController::AGargoyleController()
{
	SightSenseConfig->PeripheralVisionAngleDegrees = PERIPHERAL_VISION_ANGLE;

	SightSenseConfig->SightRadius = SIGHT_RADIUS;
	SightSenseConfig->LoseSightRadius = SIGHT_RADIUS;

	PerceptionComp->ConfigureSense(*SightSenseConfig);
}

void AGargoyleController::BeginPlay()
{
	Super::BeginPlay();

	if (AGargoyle* Gargoyle = GET_GARGOYLE)
	{
		SetStandingIndex(Gargoyle);
	}
}

void AGargoyleController::SetStandingIndex(AGargoyle* Gargoyle)
{
	TArray<APatrolPathIndicator*> StadingPoints = Gargoyle->GetStandingPoints();
	float ClosestDistance = 10000000;
	APatrolPathIndicator* CurrentStandingPos = nullptr;

	for (APatrolPathIndicator* Current : StadingPoints)
	{
		if (FVector::Dist(Gargoyle->GetActorLocation(), Current->GetActorLocation()) < ClosestDistance)
		{
			ClosestDistance = FVector::Dist(Gargoyle->GetActorLocation(), Current->GetActorLocation());
			CurrentStandingPos = Current;
		}
	}

	GetBlackboardComponent()->SetValueAsInt("LocationIndex", Gargoyle->GetStandingIndex(CurrentStandingPos));
}