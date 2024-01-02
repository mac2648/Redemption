// Fill out your copyright notice in the Description page of Project Settings.


#include "RedemptionController.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Perception/AISenseConfig_Hearing.h"

ARedemptionController::ARedemptionController()
{
	PerceptionComp = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AiPercption"));

	UAISenseConfig_Sight* SightSenseConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("SightSense"));
	SightSenseConfig->DetectionByAffiliation.bDetectEnemies = true;
	SightSenseConfig->DetectionByAffiliation.bDetectFriendlies = true;
	SightSenseConfig->DetectionByAffiliation.bDetectNeutrals = true;
	SightSenseConfig->PointOfViewBackwardOffset = 50;
	SightSenseConfig->NearClippingRadius = 50;
	SightSenseConfig->PeripheralVisionAngleDegrees = 45;
	SightSenseConfig->SightRadius = 1000;
	SightSenseConfig->LoseSightRadius = 1200;
	PerceptionComp->ConfigureSense(*SightSenseConfig);

	UAISenseConfig_Hearing* HearingSenseConfig = CreateDefaultSubobject<UAISenseConfig_Hearing>(TEXT("HearingSense"));
	HearingSenseConfig->DetectionByAffiliation.bDetectEnemies = true;
	HearingSenseConfig->DetectionByAffiliation.bDetectFriendlies = true;
	HearingSenseConfig->DetectionByAffiliation.bDetectNeutrals = true;
	HearingSenseConfig->HearingRange = 500;
	PerceptionComp->ConfigureSense(*HearingSenseConfig);
}