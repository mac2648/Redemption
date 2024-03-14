// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "QuestionMarkWidget.generated.h"

/**
 * 
 */
UCLASS()
class REDEMPTION_API UQuestionMarkWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintImplementableEvent)
	void SetOwnerActor(AActor* Actor, float ActorHeight);
};
