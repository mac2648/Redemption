// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnemyCharacter.h"
#include "Rat.generated.h"

/**
 * 
 */
UCLASS()
class REDEMPTION_API ARat : public AEnemyCharacter
{
	GENERATED_BODY()

protected:
	//component used as temporary because the rat meh is not a skeletal component yet
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* StaticMesh;

public:
	ARat();
	
};
