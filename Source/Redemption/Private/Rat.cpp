// Fill out your copyright notice in the Description page of Project Settings.

#include "Rat.h"
#include "Components/CapsuleComponent.h"
#include "PatrolComponent.h"

ARat::ARat()
{
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Temporary mesh"));
	StaticMesh->SetupAttachment(GetCapsuleComponent());

	PatrolComp = CreateDefaultSubobject<UPatrolComponent>(TEXT("PatrolComponent"));
}