// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interactable.generated.h"

DECLARE_MULTICAST_DELEGATE(FInteractableActivate)

UCLASS()
class REDEMPTION_API AInteractable : public AActor
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* Mesh;

	//event that the door will subscribe to
	FInteractableActivate OnActivate;

	bool IsActive = false;
	
public:	
	// Sets default values for this actor's properties
	AInteractable();

	//function that will broadcast the OnActive event
	virtual void Activate();
	bool GetIsActive() { return IsActive; }

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};
