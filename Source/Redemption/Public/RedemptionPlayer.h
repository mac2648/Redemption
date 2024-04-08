// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Components/WidgetComponent.h"
#include "DevTools.h"
#include "RedemptionPlayer.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UInputAction;
struct FInputActionValue;
class UPowerUpComponent;
class UHealthComponent;
class UStaminaBarWidget;
class USoundCue;

UCLASS()
class REDEMPTION_API ARedemptionPlayer : public ACharacter
{
	GENERATED_BODY()

public:
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return TPPCamera; }

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* TPPCamera;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FPPCamera;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
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

	//No preprocessors here because UPROPERTY cannot be inside of one
	//---------------------- PLAYTEST TOOLS VARIABLES -------------------------------------------------------------------------
	UPROPERTY(EditDefaultsOnly, Category = "DevTools")
	UInputAction* ChangePowerAction;

	UPROPERTY(EditDefaultsOnly, Category = "DevTools")
	UInputAction* RecoverHealthAction;

	UPROPERTY(EditDefaultsOnly, Category = "DevTools")
	TSubclassOf<UUserWidget> ChoosePowerUpWidgetClass;
	//---------------------- END OF PLAYTEST TOOLS VARIABLES ------------------------------------------------------------------

	UPROPERTY(EditDefaultsOnly)
	USoundCue* FootStepsCue = nullptr;

	//time handle used for the footsteps timer
	FTimerHandle FootStepsHandle;
	float StepVolume = 1.0f;

	FTimerHandle FallNoiseHandle;
	//the amount of frames the falling noise UI will be in the screen
	int FallNoiseFrames = 0;

	bool NeedToStopSprinting = false;

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

	//Player Noise Detection
	float PlayerNoise = 0;

	// HUD widget for stamina
	UPROPERTY(EditAnywhere, Category = "HUD")
	TSubclassOf<UStaminaBarWidget> StaminaWidgetClass;

	UPROPERTY()
	UStaminaBarWidget* StaminaWidget;

	UPROPERTY(EditAnywhere, Category = "HUD")
	TSubclassOf<UUserWidget> PauseWidgetClass;

	// HUD Widget for Noise Detector
	UPROPERTY(EditAnywhere, Category = "HUD")
	TSubclassOf<UUserWidget> NoiseWidgetClass;

	// Functions
	void StartSprinting();
	void StopSprinting();
	void UpdateStaminaWidget(float StaminaPercent);

public:
	ARedemptionPlayer();
	UHealthComponent* GetHealthComponent() const { return HealthComp; }
	UPowerUpComponent* GetPowerUpComponent() const { return PowerUpComp; }
	UCameraComponent* GetFPPCamera() { return FPPCamera; }

	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable)
	float GetPlayerNoise() { return PlayerNoise; }

protected:
	virtual void BeginPlay() override;

	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	void StartCrouch();
	void EndCrouch();
	void LauchPauseMenu();
	void StepSound();

#ifdef PLAYTEST_TOOLS
	void RecoverHealth();
	void ChangePowerUp();
#endif

	//tick functions
	void TickSprint(float DeltaTime);
	void TickStamina();
	void TickNoiseReporting();

	//function used to find when the player reaches the ground
	void NotifyAIOfFall();
};
