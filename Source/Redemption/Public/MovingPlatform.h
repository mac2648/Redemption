// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MovingPlatform.generated.h"

#define ACCEPTANCE_DISTANCE 5

class AInteractable;

UCLASS()
class REDEMPTION_API AMovingPlatform : public AActor
{
	GENERATED_BODY()

protected:
	//list of interactables that need to be activated for it to start moving
	UPROPERTY(EditAnywhere, category = "Keys")
	TArray<AInteractable*> Keys;

	//if false the platform will move once and stop in the new position
	UPROPERTY(EditAnywhere, category = "Movement")
	bool IsLooping = true;

	UPROPERTY(EditAnywhere, category = "Movement")
	FVector MoveDistance;

	UPROPERTY(EditAnywhere, category = "Mesh")
	UStaticMeshComponent* Mesh;

	UPROPERTY(EditAnywhere, category = "Movement")
	float Speed = 200;

	FVector InitialPos;
	bool IsMoving = false;
	bool IsGoingBack = false;
	bool IsDeactivating = false;
	
public:	
	AMovingPlatform();

	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	void CheckMoveConditions();
	void Move(float DeltaTime);

	void MoveToInitialPostion(float DeltaTime);
	void MoveToTargetLocation(float DeltaTime);
};
