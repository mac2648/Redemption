// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PowerUpComponent.generated.h"

class UInputAction;
class UInputMappingContext;
struct FInputActionValue;

enum EActivePowerUp
{
	None,
	BoneThrow,
	Parry,
	Hover
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class REDEMPTION_API UPowerUpComponent : public UActorComponent
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputMappingContext* BoneMappingContext;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputMappingContext* HoverMappingContext;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputMappingContext* ParryMappingContext;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputAction* UsePowerUpAction;

	EActivePowerUp CurrentPowerUp = EActivePowerUp::BoneThrow;

public:	
	// Sets default values for this component's properties
	UPowerUpComponent();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void UsePowerUp(const FInputActionValue& Value);

	EActivePowerUp GetActivePowerUp() const { return CurrentPowerUp; }

	UInputAction* GetUsePowerAction() const { return UsePowerUpAction; }

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	void ChangeMappingContext();
};
