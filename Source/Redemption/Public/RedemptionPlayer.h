// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Components/WidgetComponent.h"
#include "RedemptionPlayer.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UInputAction;
struct FInputActionValue;
class UPowerUpComponent;
class UHealthComponent;

UCLASS()
class REDEMPTION_API ARedemptionPlayer : public ACharacter
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* TPPCamera;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FPPCamera;

	UPROPERTY(EditDefaultsOnly)
	UPowerUpComponent* PowerUpComp;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputMappingContext* DefaultMappingContext;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputMappingContext* TPPMappingContext;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputAction* JumpAction;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputAction* MoveAction;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputAction* LookAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UHealthComponent* HealthComp;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputAction* CrouchAction;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	const UInputAction* SprintAction;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	const UInputAction* PauseAction;




private:
	// Stamina settings
	UPROPERTY(VisibleAnywhere, Category = "Stamina")
	float Stamina;

	UPROPERTY(EditDefaultsOnly, Category = "Stamina")
	float MaxStamina;

	UPROPERTY(EditDefaultsOnly, Category = "Stamina")
	float StaminaDepletionRate;

	UPROPERTY(EditDefaultsOnly, Category = "Stamina")
	float StaminaRegenerationRate;

	UPROPERTY(VisibleAnywhere, Category = "Stamina")
	bool bCanSprint;

	UPROPERTY(VisibleAnywhere, Category = "Stamina")
	bool bIsSprinting;

	UPROPERTY(EditDefaultsOnly, Category = "Stamina")
	float MaxSprintSpeed;

	// HUD widget for stamina
	UPROPERTY(EditAnywhere, Category = "HUD")
	TSubclassOf<UUserWidget> StaminaWidgetClass;

	UPROPERTY()
	UUserWidget* StaminaWidget;

	UPROPERTY(EditAnywhere, Category = "HUD")
	TSubclassOf<UUserWidget> PauseWidgetClass;


	// Functions
	void StartSprinting();
	void StopSprinting();
	void UpdateStaminaWidget(float StaminaPercent);

public:
	ARedemptionPlayer();
	UHealthComponent* GetHealthComponent() const { return HealthComp; }

	UCameraComponent* GetFPPCamera() { return FPPCamera; }

protected:
	virtual void BeginPlay() override;

	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	void StartCrouch();
	void EndCrouch();
	void LauchPauseMenu();

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return TPPCamera; }
};
