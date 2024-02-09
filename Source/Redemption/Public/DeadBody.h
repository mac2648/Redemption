// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DeadBody.generated.h"

class UInteractWidgetComponent;

UCLASS()
class REDEMPTION_API ADeadBody : public AActor
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere)
	USkeletalMeshComponent* Mesh;

	UPROPERTY(EditAnywhere)
	UInteractWidgetComponent* InteractComp;
	
public:	
	// Sets default values for this actor's properties
	ADeadBody();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
