// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"
#include "Components/WidgetComponent.h"
#include "GameFramework/Controller.h"
#include "RedemptionPlayer.h"
#include "RedemptionGameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/UserWidget.h"
#include "PowerUpComponent.h"
#include "../RedemptionGameMode.h"
#include "Sound/SoundCue.h"
#include "Kismet/KismetStringLibrary.h"
#include "RedemptionUtils.h"

#define INVUL_DURATION 1.5

// Sets default values for this component's properties
UHealthComponent::UHealthComponent() :
Health{ MaxHealth }
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

}


// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	GetOwner()->OnTakeAnyDamage.AddDynamic(this, &UHealthComponent::TakeDamage);
}


// Called every frame
void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

float UHealthComponent::GetHealth() const
{
	return Health;
}

float UHealthComponent::GetMaxHealth() const
{
	return MaxHealth;
}

void UHealthComponent::SetHealth(float const NewHealth)
{
	Health = NewHealth;

    if (Health > MaxHealth)
    {
        Health = MaxHealth;
    }

    if (Health > 1 && CurrentVignetteWidget)
    {
        CurrentVignetteWidget->RemoveFromViewport();
        CurrentVignetteWidget = nullptr;
    }
}

void UHealthComponent::Die()
{
	URedemptionGameInstance* Instance = Cast<URedemptionGameInstance>(GetOwner()->GetGameInstance());

    if (Instance)
    {
        int32 WorldId = RedemptionUtils::GetWorldID(GetWorld());

        Instance->SetPlayerDiedLocation(WorldId);
        Instance->SetupSaveInfo();
        Instance->SaveGame();
    }

    if (ARedemptionGameMode* GameMode = Cast<ARedemptionGameMode>(UGameplayStatics::GetGameMode(GetWorld())))
    {
        GameMode->DestroyInteractableActors();
    }

	GameOver();
}


void UHealthComponent::GameOver()
{
	UUserWidget* GameOverWidget = CreateWidget<UUserWidget>(GetWorld(), GameOverWidgetClass);
	GameOverWidget->AddToViewport();
}

void UHealthComponent::TakeDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser)
{
    if (ARedemptionPlayer* Player = Cast<ARedemptionPlayer>(GetOwner()))
    {
        if (UPowerUpComponent* PowerComp = Player->GetPowerUpComponent())
        {
            if (PowerComp->GetActivePowerUp() == EActivePowerUp::Parry && PowerComp->GetIsParrying())
            {
                return;
            }
        }
    }

    if (IsInvunerable)
    {
        return;
    }

    Health -= Damage;
    UGameplayStatics::PlaySound2D(GetWorld(), PlayerHitCue,1.0f, 1.0f, 0.04f);

    if (Health <= 0)
    {
        Die();
    }
    else if (Health == 1 && !CurrentVignetteWidget)
    {
        UWorld* World = GetWorld();
        if (World)
        {
            CurrentVignetteWidget = CreateWidget<UUserWidget>(World, VignetteWidgetClass);
            if (CurrentVignetteWidget)
            {
                CurrentVignetteWidget->AddToViewport(0);
                CurrentVignetteWidget->SetVisibility(ESlateVisibility::HitTestInvisible);
            }
        }
       
    }
    else if (Health > 1 && CurrentVignetteWidget)
    {
        CurrentVignetteWidget->RemoveFromViewport();
        CurrentVignetteWidget = nullptr;
    }

    IsInvunerable = true;


    FTimerHandle InvunerableDelegate;
    //sets a timer for when the invulnerabiity will end
    GetWorld()->GetTimerManager().SetTimer(InvunerableDelegate, this, &UHealthComponent::ResetInvunerability, INVUL_DURATION);
}
