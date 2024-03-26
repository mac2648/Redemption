// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interactable.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FInteractableActivate);

class ALevelSequenceActor;

UCLASS()
class REDEMPTION_API AInteractable : public AActor
{
	GENERATED_BODY()

public:
	//event that the door will subscribe to
	FInteractableActivate OnActivate;

protected:
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* BaseMesh;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* PuzzleMesh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	ALevelSequenceActor* LeverSequence;

	bool IsActive = false;
	
public:	
	// Sets default values for this actor's properties
	AInteractable();

	//function that will broadcast the OnActive event
	virtual void Activate();
	bool GetIsActive() { return IsActive; }

	UFUNCTION(BlueprintImplementableEvent)
	void ShowSequence();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};
