// Copyright Epic Games, Inc. All Rights Reserved.

#include "RedemptionGameMode.h"
#include "RedemptionCharacter.h"
#include "UObject/ConstructorHelpers.h"

ARedemptionGameMode::ARedemptionGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
