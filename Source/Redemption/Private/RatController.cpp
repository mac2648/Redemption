// Fill out your copyright notice in the Description page of Project Settings.


#include "RatController.h"
#include "Perception/AISenseConfig_Sight.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Rat.h"

void ARatController::UpdateSight(AActor* Actor, FAIStimulus Stimulus)
{
	if (Actor == UGameplayStatics::GetPlayerPawn(GetWorld(), 0))
	{ 
		if (Stimulus.WasSuccessfullySensed())
		{
			GetBlackboardComponent()->SetValueAsObject("Player", Actor);
			if (UCharacterMovementComponent* MoveComp = Cast<ACharacter>(GetPawn())->GetCharacterMovement())
			{
				MoveComp->MaxWalkSpeed = 370;
			}
		}
		else
		{
			GetBlackboardComponent()->SetValueAsVector("LastSeenLocation", Stimulus.StimulusLocation);
			GetBlackboardComponent()->ClearValue("Player");
			if (UCharacterMovementComponent* MoveComp = Cast<ACharacter>(GetPawn())->GetCharacterMovement())
			{
				MoveComp->MaxWalkSpeed = 150;
			}
		}
		OnPlayerSightUpdate.Broadcast();
	}
}