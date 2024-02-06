// Copyright Epic Games, Inc. All Rights Reserved.

#include "RedemptionGameMode.h"
#include "RedemptionCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "AudioManager.h" 
#include "Kismet/GameplayStatics.h" 

ARedemptionGameMode::ARedemptionGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}

void ARedemptionGameMode::BeginPlay()
{
    Super::BeginPlay();
    MyAudioManager = Cast<AudioManager>(UGameplayStatics::GetActorOfClass(GetWorld(), AudioManager::StaticClass()));

    if (MyAudioManager)
    {
        MyAudioManager->PlayAmbientMusic();
    }
}

void ARedemptionGameMode::HandleGameStateChange(EGameState NewState)
{
    if (!MyAudioManager)
    {
        UE_LOG(LogTemp, Warning, TEXT("AudioManager is not initialized."));
        return;
    }

    switch (NewState)
    {
    case EGameState::Safe:
        MyAudioManager->PlayAmbientMusic();
        break;

    case EGameState::InCombat:
        MyAudioManager->PlayCombatMusic();
        break;

    default:
        break;
    }
}