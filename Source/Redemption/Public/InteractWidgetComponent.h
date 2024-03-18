// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InteractWidgetComponent.generated.h"

class UInputMappingContext;
class UInputAction;
class UBoxComponent;
struct FInputBindingHandle;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class REDEMPTION_API UInteractWidgetComponent : public UActorComponent
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere)
	UBoxComponent* BoxComp;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputMappingContext* InteractMappingContext;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputAction* InteractAction;

	UPROPERTY(EditDefaultsOnly, category = "Widget")
	TSubclassOf<UUserWidget> InteractWidgetClass;

	UUserWidget* InteractWidget = nullptr;
	FInputBindingHandle* BindedAction;

public:	
	// Sets default values for this component's properties
	UInteractWidgetComponent();

	UBoxComponent* GetBoxComp() { return BoxComp; }

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	void Interract();
	void FirstCheck();
};