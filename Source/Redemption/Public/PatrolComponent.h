// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PatrolComponent.generated.h"

class APatrolPathIndicator;

UENUM()
enum EPatrolType
{
	Loop UMETA(DisplayName = "Loop"),
	GoBack UMETA(DisplayName = "GoBack")
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class REDEMPTION_API UPatrolComponent : public UActorComponent
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere)
	TMap<APatrolPathIndicator*, float> PatrolPath;

	UPROPERTY(EditAnywhere)
	TEnumAsByte<EPatrolType> PatrolType;

	//1 = normal movement, -1 = going back
	short PatrolDirection = 1;

public:	
	// Sets default values for this component's properties
	UPatrolComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	const TMap<APatrolPathIndicator*, float>* GetPatrolPath() const { return &PatrolPath; }
	EPatrolType GetPatrolType() { return PatrolType; }
	short GetPatrolDirection() { return PatrolDirection; }
	void InverseDirection() { PatrolDirection *= -1; }
};
