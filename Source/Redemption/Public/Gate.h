// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Gate.generated.h"

class AInteractable;

UCLASS()
class REDEMPTION_API AGate : public AActor
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere)
	TMap<AInteractable*, bool> InteractableKeys;

	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* Mesh;

	UPROPERTY(EditAnywhere)
	float MoveAngle = 90;

	FRotator OpenedRotation = FRotator::ZeroRotator;
	FRotator ClosedRotation = FRotator::ZeroRotator;

	bool IsOpen = false;
	
public:	
	// Sets default values for this actor's properties
	AGate();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//when there is a change in any of the interactables it will call this function to check if the door should open or not
	UFUNCTION()
	void CheckOpenConditions();
	void RotateGate();
};
