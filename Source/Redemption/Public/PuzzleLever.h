// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interactable.h"
#include "PuzzleLever.generated.h"


class USoundCue;
class UInteractWidgetComponent;
/**
 * 
 */
UCLASS()
class REDEMPTION_API APuzzleLever : public AInteractable
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(EditAnywhere)
	UInteractWidgetComponent* InteractComp;
	UPROPERTY(EditDefaultsOnly)
	USoundCue* SwitchCue = nullptr;

	bool IsRotating = false;

public:
	APuzzleLever();

	virtual void Activate() override;

	virtual void Tick(float DeltaTime) override;
};
