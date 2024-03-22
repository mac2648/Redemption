// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Interface_Localization.generated.h"

class UFont;

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UInterface_Localization : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class REDEMPTION_API IInterface_Localization
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	virtual UFont* SetFontPerLanguage() const;
};
