// Fill out your copyright notice in the Description page of Project Settings.

#include "GargoyleController.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"

const int PERIPHERAL_VISION_ANGLE = 60;
const int SIGHT_RADIUS = 3000;

AGargoyleController::AGargoyleController()
{
	SightSenseConfig->PeripheralVisionAngleDegrees = PERIPHERAL_VISION_ANGLE;

	SightSenseConfig->SightRadius = SIGHT_RADIUS;
	SightSenseConfig->LoseSightRadius = SIGHT_RADIUS;

	PerceptionComp->ConfigureSense(*SightSenseConfig);
}