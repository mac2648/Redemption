// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Crow.generated.h"

class UFloatingPawnMovement;
class UCapsuleComponent;

UCLASS()
class REDEMPTION_API ACrow : public APawn
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleAnywhere)
	UCapsuleComponent* CapsuleComp;

	//will later change to a skeletal mesh when asset is ready
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* Mesh;

	UPROPERTY(VisibleAnywhere)
	UFloatingPawnMovement* MovementComp;

public:
	// Sets default values for this pawn's properties
	ACrow();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
