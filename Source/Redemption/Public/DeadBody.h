// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DeadBody.generated.h"

class UInteractWidgetComponent;
class UBoxComponent;

UCLASS()
class REDEMPTION_API ADeadBody : public AActor
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere)
	USkeletalMeshComponent* Mesh;

	UPROPERTY(EditAnywhere)
	UInteractWidgetComponent* InteractComp;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> ChangePowerUpWidgetClass;

	UBoxComponent* BoxComp = nullptr;
	
public:	
	// Sets default values for this actor's properties
	ADeadBody();

	void CreateChangePowerUpWidget();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
