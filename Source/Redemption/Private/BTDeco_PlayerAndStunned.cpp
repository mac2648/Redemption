// Fill out your copyright notice in the Description page of Project Settings.


#include "BTDeco_PlayerAndStunned.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTDeco_PlayerAndStunned::UBTDeco_PlayerAndStunned()
{
	NodeName = "CanSeePlayer || IsStuned";
}

//execution of the decorator
bool UBTDeco_PlayerAndStunned::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	bool Stuned = OwnerComp.GetBlackboardComponent()->GetValueAsBool(IsStuned.SelectedKeyName);

	if (Stuned)
	{
		return true;
	}

	UObject* PlayerObj = OwnerComp.GetBlackboardComponent()->GetValueAsObject(Player.SelectedKeyName);

	//if player is set
	if (PlayerObj)
	{
		return true;
	}

	bool Attacking = OwnerComp.GetBlackboardComponent()->GetValueAsBool(IsAttacking.SelectedKeyName);

	if (Attacking)
	{
		return true;
	}

	return false;
}