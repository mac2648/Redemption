// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Gargoyle.generated.h"

class UFloatingPawnMovement;
class UCapsuleComponent;
class APatrolPathIndicator;

UCLASS()
class REDEMPTION_API AGargoyle : public APawn
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleAnywhere)
	UFloatingPawnMovement* FloatMovementComp;

	UPROPERTY(EditDefaultsOnly)
	USkeletalMeshComponent* SkeletalMesh;

	UPROPERTY(VisibleAnywhere)
	UCapsuleComponent* CapsuleComp;

	UPROPERTY(EditAnywhere, category = "Patrol")
	TArray<APatrolPathIndicator*> StandingPoints;

public:
	// Sets default values for this pawn's properties
	AGargoyle();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFloatingPawnMovement* GetFloatMovementComp() const { return FloatMovementComp; }
	APatrolPathIndicator* GetStandingPoint(int Index) const { return StandingPoints[Index]; }
	//returns -1 if the point is not part of the array
	int GetStandingIndex(APatrolPathIndicator* Point) const;
	TArray<APatrolPathIndicator*> GetStandingPoints() const { return StandingPoints; }

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};
