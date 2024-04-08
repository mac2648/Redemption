// Copyright Epic Games, Inc. All Rights Reserved.

#include "RedemptionGameMode.h"
#include "RedemptionCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "AudioManager.h" 
#include "Kismet/GameplayStatics.h" 
#include "LandEnemyController.h"
#include "AIController.h"
#include "RedemptionGameInstance.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "DeadBody.h"
#include "RedemptionUtils.h"
#include "InteractWidgetComponent.h"
#include "FontManager.h"

ARedemptionGameMode::ARedemptionGameMode()
{
	// set default pawn class to our Blueprinted character
    PrimaryActorTick.bCanEverTick = false;
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}

void ARedemptionGameMode::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void ARedemptionGameMode::BeginPlay()
{
    Super::BeginPlay();
    MyAudioManager = Cast<AAudioManager>(UGameplayStatics::GetActorOfClass(GetWorld(), AAudioManager::StaticClass()));
    TArray<AActor*> EnemiesActors;
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), ALandEnemyController::StaticClass(), EnemiesActors);


    for (AActor* Current : EnemiesActors)
    {
        Enemies.Push(Cast<ALandEnemyController>(Current));
    }

    for (ALandEnemyController* Current : Enemies)
    {
        Current->OnPlayerSightUpdate.AddDynamic(this, &ARedemptionGameMode::HandlePlayerSightUpdate);
    }

    if (MyAudioManager)
    {
        MyAudioManager->PlayAmbientMusic();
    }

    URedemptionGameInstance* Instance = Cast<URedemptionGameInstance>(GetGameInstance());
    FVector PlayerBodyPosition = Instance->GetPlayerDiedLocation();

    if (PlayerBodyPosition != FVector::ZeroVector)
    {
        GetWorld()->SpawnActor<AActor>(DeadBodyClass, PlayerBodyPosition, FRotator::ZeroRotator);
    }
}

void ARedemptionGameMode::HandleGameStateChange(EGameState NewState)
{
    if (!MyAudioManager)
    {
        return;
    }

    switch (NewState)
    {
    case EGameState::Safe:
        MyAudioManager->ResetCombatState();
        break;

    case EGameState::InCombat:
        MyAudioManager->PlayCombatMusic();
        break;

    default:
        break;
    }
}

void ARedemptionGameMode::DestroyInteractableActors()
{
    TArray<AActor*> InteractableActors;

    RedemptionUtils::GetAllActorsWithComponentByClass<UInteractWidgetComponent>(GetWorld(), InteractableActors);

    for (AActor* Current : InteractableActors)
    {
        Current->Destroy();
    }
}

void ARedemptionGameMode::HandlePlayerSightUpdate()
{
    bool Safe = true;
    for (ALandEnemyController* Curr : Enemies)
    {
        UObject* ptr = Curr->GetBlackboardComponent()->GetValueAsObject("Player");
        if (ptr != nullptr)
        {
            Safe = false;
            break;
        }
    }

    if (Safe && !SafeMusic)
    {
        SafeMusic = true;
        HandleGameStateChange(EGameState::Safe);

    }
    else if (!Safe && SafeMusic)
    {
        SafeMusic = false;
        HandleGameStateChange(EGameState::InCombat);
    }
}