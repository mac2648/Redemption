// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ChangePowerUpWidget.generated.h"


class UButton;
enum EActivePowerUp;
class UPowerUpComponent;
/**
 * 
 */
UCLASS()
class REDEMPTION_API UChangePowerUpWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UButton* BoneButton;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UButton* ParryButton;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UButton* HoverButton;

	UPowerUpComponent* PlayerPowerUpComp = nullptr;

public:
	virtual void NativeConstruct() override;
	
	UFUNCTION()
	void ActivateBonePower();

	UFUNCTION()
	void ActivateParryPower();

	UFUNCTION()
	void ActivateHoverPower();

	void Delete();
};
