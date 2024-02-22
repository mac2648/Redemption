// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PowerUpComponent.generated.h"

const float BONE_CD = 1.0f;

class UInputAction;
class UInputMappingContext;
struct FInputActionValue;
class ABone;

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

	UPROPERTY(EditDefaultsOnly, category = "Power")
	float BoneCD = BONE_CD;

	EActivePowerUp CurrentPowerUp = EActivePowerUp::Parry;

	bool IsParring = false;

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
	bool GetIsParring() { return IsParring; }

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	void ChangeMappingContext();

	//will spawn the bone
	void ExecuteBonePowerUp();

	void ExecuteParryPowerUp(bool NewParry);
};
