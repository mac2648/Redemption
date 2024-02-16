// Fill out your copyright notice in the Description page of Project Settings.

#include "GargoyleController.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Gargoyle.h"
#include "PatrolPathIndicator.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"

#define GET_GARGOYLE Cast<AGargoyle>(GetPawn())

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

	GetBlackboardComponent()->SetValueAsBool("IsLanded", true);
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

void AGargoyleController::UpdateSight(AActor* Actor, FAIStimulus Stimulus)
{
	bool IsLanded = GetBlackboardComponent()->GetValueAsBool("IsLanded");

	if (Actor == UGameplayStatics::GetPlayerPawn(GetWorld(), 0))
	{
		if (Stimulus.WasSuccessfullySensed() && IsLanded)
		{
			GetBlackboardComponent()->SetValueAsObject("Player", Actor);
		}
		else if (!Stimulus.WasSuccessfullySensed() && IsLanded)
		{
			GetBlackboardComponent()->ClearValue("Player");
			GetBlackboardComponent()->SetValueAsVector("LastSeenLocation", Stimulus.StimulusLocation);
		}
		else
		{
			GetBlackboardComponent()->SetValueAsVector("LastSeenLocation", Stimulus.StimulusLocation);
		}
	}
}