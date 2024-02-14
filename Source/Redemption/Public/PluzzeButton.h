// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interactable.h"
#include "PluzzeButton.generated.h"

class UBoxComponent;
/**
 * 
 */
UCLASS()
class REDEMPTION_API APluzzeButton : public AInteractable
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(EditAnywhere)
	UBoxComponent* BoxComp;

public:
	APluzzeButton();

	virtual void Activate() override;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
