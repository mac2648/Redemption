// Fill out your copyright notice in the Description page of Project Settings.


#include "RedemptionController.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"

ARedemptionController::ARedemptionController()
{
	PerceptionComp = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AiPercption"));

	SightSenseConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("SightSense"));

	SightSenseConfig->DetectionByAffiliation.bDetectEnemies = true;
	SightSenseConfig->DetectionByAffiliation.bDetectFriendlies = true;
	SightSenseConfig->DetectionByAffiliation.bDetectNeutrals = true;

	SightSenseConfig->PointOfViewBackwardOffset = 50;

	SightSenseConfig->NearClippingRadius = 50;

	SightSenseConfig->PeripheralVisionAngleDegrees = 45;

	SightSenseConfig->SightRadius = 1000;
	SightSenseConfig->LoseSightRadius = 1200;

	PerceptionComp->ConfigureSense(*SightSenseConfig);
}

void ARedemptionController::BeginPlay()
{
	Super::BeginPlay();

	if (Tree)
	{
		RunBehaviorTree(Tree);
	}

	PerceptionComp->OnTargetPerceptionUpdated.AddDynamic(this, &ARedemptionController::UpdateTargetPerception);
}

void ARedemptionController::UpdateTargetPerception(AActor* Actor, FAIStimulus Stimulus)
{
	if (Stimulus.Type == UAISense::GetSenseID(UAISense_Sight::StaticClass()))
	{
		UpdateSight(Actor, Stimulus);
	}
}

void ARedemptionController::UpdateSight(AActor* Actor, FAIStimulus Stimulus)
{
	if (Actor == UGameplayStatics::GetPlayerPawn(GetWorld(), 0))
	{
		if (Stimulus.WasSuccessfullySensed())
		{
			GetBlackboardComponent()->SetValueAsObject("Player", Actor);
		}
		else
		{
			GetBlackboardComponent()->SetValueAsVector("LastSeenLocation", Stimulus.StimulusLocation);
			GetBlackboardComponent()->ClearValue("Player");
		}
	}
}