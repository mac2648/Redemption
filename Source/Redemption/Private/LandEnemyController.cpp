// Fill out your copyright notice in the Description page of Project Settings.

#include "LandEnemyController.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Perception/AISenseConfig_Hearing.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"

const int BASE_HEARING_RADIUS = 500;

ALandEnemyController::ALandEnemyController()
{
	HearingSenseConfig = CreateDefaultSubobject<UAISenseConfig_Hearing>(TEXT("HearingSense"));

	HearingSenseConfig->DetectionByAffiliation.bDetectEnemies = true;
	HearingSenseConfig->DetectionByAffiliation.bDetectFriendlies = true;
	HearingSenseConfig->DetectionByAffiliation.bDetectNeutrals = true;
	HearingSenseConfig->HearingRange = BASE_HEARING_RADIUS;

	PerceptionComp->ConfigureSense(*HearingSenseConfig);
}

void ALandEnemyController::BeginPlay()
{
	Super::BeginPlay();
}

void ALandEnemyController::UpdateTargetPerception(AActor* Actor, FAIStimulus Stimulus)
{
	if (Stimulus.Type == UAISense::GetSenseID(UAISense_Sight::StaticClass()))
	{
		UpdateSight(Actor, Stimulus);
	}
	else if (Stimulus.Type == UAISense::GetSenseID(UAISense_Hearing::StaticClass()))
	{
		UpdateHearing(Stimulus);
	}
}

void ALandEnemyController::UpdateSight(AActor* Actor, FAIStimulus Stimulus)
{
	if (Actor == UGameplayStatics::GetPlayerPawn(GetWorld(), 0))
	{
		if (Stimulus.WasSuccessfullySensed())
		{
			GetBlackboardComponent()->SetValueAsObject("Player", Actor);
			GetBlackboardComponent()->ClearValue("LastNoiseLocation");
		}
		else
		{
			GetBlackboardComponent()->SetValueAsVector("LastSeenLocation", Stimulus.StimulusLocation);
			GetBlackboardComponent()->ClearValue("Player");
		}
		OnPlayerSightUpdate.Broadcast();
	}
}

void ALandEnemyController::UpdateHearing(FAIStimulus Stimulus)
{
	if (Stimulus.WasSuccessfullySensed())
	{
		GetBlackboardComponent()->SetValueAsVector("LastNoiseLocation", Stimulus.StimulusLocation);
	}
}