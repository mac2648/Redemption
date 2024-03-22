// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "LocalizationGameMode.generated.h"

/**
 * 
 */
class AFontManager;

UCLASS()
class REDEMPTION_API ALocalizationGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
public:

	UPROPERTY(EditDefaultsOnly, category = "Font")
	TSubclassOf<AFontManager> FontManagerClass;

	AFontManager* FontManagerInstance;

public:

	virtual void BeginPlay();

	AFontManager* GetFontManagerInstance() { return FontManagerInstance; }
};
