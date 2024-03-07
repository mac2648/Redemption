// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PowerUpComponent.generated.h"

const float BONE_CD = 1.0f;
const float PARRY_MAX_ENERGY = 100.0f;
const float PARRY_DEPLETION_RATE = 50.0f;
const float PARRY_FILL_RATE = 10.0f;

class UInputAction;
class UInputMappingContext;
struct FInputActionValue;
class ABone;
class UParryBarWidget;

UENUM(BlueprintType)
enum EActivePowerUp
{
	None UMETA(DisplayName = "None"),
	BoneThrow UMETA(DisplayName = "Bone Throw"),
	Parry UMETA(DisplayName = "Parry"),
	Hover UMETA(DisplayName = "Hover")
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

	UPROPERTY(EditDefaultsOnly, Category = "Power")
	TSubclassOf<ABone> BoneBP;

	UPROPERTY(EditDefaultsOnly, category = "UI")
	TSubclassOf<UParryBarWidget> ParryBarWidgetClass;

	float BoneCD = BONE_CD;
	float ParryEnergy = PARRY_MAX_ENERGY;
	UParryBarWidget* ParryBar = nullptr;

	EActivePowerUp CurrentPowerUp = EActivePowerUp::BoneThrow;

	bool IsParrying = false;

public:	
	// Sets default values for this component's properties
	UPowerUpComponent();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void UsePowerUp(const FInputActionValue& Value);

	EActivePowerUp GetActivePowerUp() const { return CurrentPowerUp; }

	UInputAction* GetUsePowerAction() const { return UsePowerUpAction; }

	UFUNCTION(BlueprintCallable)
	void ChangeActivePowerUp(EActivePowerUp NewPower);
	bool GetIsParrying() const { return IsParrying; }
	float GetParryEnergyPercentage() const { return ParryEnergy / PARRY_MAX_ENERGY; }

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	void ChangeMappingContext();

	//will spawn the bone
	void ExecuteBonePowerUp();

	void ExecuteParryPowerUp(bool NewParry);
};
