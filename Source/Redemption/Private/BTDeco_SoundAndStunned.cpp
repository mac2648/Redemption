// Fill out your copyright notice in the Description page of Project Settings.


#include "BTDeco_SoundAndStunned.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTDeco_SoundAndStunned::UBTDeco_SoundAndStunned()
{
	NodeName = "Sound || IsAttacking";
}

//execution of the decorator
bool UBTDeco_SoundAndStunned::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	bool Attacking = OwnerComp.GetBlackboardComponent()->GetValueAsBool(IsAttacking.SelectedKeyName);

	if (Attacking)
	{
		return true;
	}

	FVector SoundLocation = OwnerComp.GetBlackboardComponent()->GetValueAsVector(LastSoundLocation.SelectedKeyName);

	//if player is set
	if (SoundLocation != FVector::ZeroVector)
	{
		return true;
	}

	return false;
}