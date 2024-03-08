// Copyright Epic Games, Inc. All Rights Reserved.

#include "RedemptionGameMode.h"
#include "RedemptionCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "AudioManager.h" 
#include "Kismet/GameplayStatics.h" 
#include "EnemyCharacter.h"
#include "AIController.h"
#include "RedemptionGameInstance.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "DeadBody.h"

ARedemptionGameMode::ARedemptionGameMode()
{
	// set default pawn class to our Blueprinted character
    PrimaryActorTick.bCanEverTick = true;
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}


}

void ARedemptionGameMode::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    bool Safe = true;
    for (AEnemyCharacter* Curr : Enemies)
    {
        
        AAIController* Enem = Cast<AAIController>(Curr->GetController());
        UObject* ptr = Enem->GetBlackboardComponent()->GetValueAsObject("Player");
        if (ptr != nullptr)
        {
            Safe = false;
            break;
        }
    }

    if (Safe && !SafeMusic)
    {
        HandleGameStateChange(EGameState::Safe);
        SafeMusic = true;

        if (MyAudioManager)
        {
            MyAudioManager->ResetCombatState();
        }
    }
    else if (!Safe && SafeMusic)
    {
        HandleGameStateChange(EGameState::InCombat);
        SafeMusic = false;
    }
}

void ARedemptionGameMode::BeginPlay()
{
    Super::BeginPlay();
    MyAudioManager = Cast<AAudioManager>(UGameplayStatics::GetActorOfClass(GetWorld(), AAudioManager::StaticClass()));
    TArray<AActor*> EnemiesActors;
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), AEnemyCharacter::StaticClass(), EnemiesActors);

    for (AActor* Current : EnemiesActors)
    {
        Enemies.Push(Cast<AEnemyCharacter>(Current));
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

void ARedemptionGameMode::DestroyDeadBodies()
{
    TArray<AActor*> DeadBodiesActors;

    UGameplayStatics::GetAllActorsOfClass(GetWorld(), ADeadBody::StaticClass(), DeadBodiesActors);

    TArray<ADeadBody*> DeadBodies;

    for (AActor* Actor : DeadBodiesActors)
    {
        if (ADeadBody* Body = Cast<ADeadBody>(Actor))
        {
            DeadBodies.Add(Body);
        }
    }

    for (ADeadBody* Body : DeadBodies)
    {
        Body->Destroy();
    }
}