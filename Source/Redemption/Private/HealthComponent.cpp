// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"
#include "Components/WidgetComponent.h"
#include "GameFramework/Controller.h"
#include "RedemptionPlayer.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/UserWidget.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent() :
WidgetComponent{ CreateDefaultSubobject<UWidgetComponent>(TEXT("HealthValue")) },
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

	if (UHealthBarWidget* const widget = Cast<UHealthBarWidget>(WidgetComponent->GetUserWidgetObject()))
	{
		widget->SetBarValuePercent(Health / MaxHealth);
	}
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
}

void UHealthComponent::Die()
{
	ACharacter* myCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	FVector PlayerDiedLocation = myCharacter->GetActorLocation();

	GameOver();
}


void UHealthComponent::GameOver()
{
	UUserWidget* GameOverWidget = CreateWidget<UUserWidget>(GetWorld(), GameOverWidgetClass);
	GameOverWidget->AddToViewport();
}

void UHealthComponent::TakeDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser)
{
    Health -= Damage;

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
                CurrentVignetteWidget->AddToViewport();
            }
            else
            {
                UE_LOG(LogTemp, Error, TEXT("Failed to create widget"));
            }
        }
       
    }

    else if (Health > 1 && CurrentVignetteWidget)
    {
        CurrentVignetteWidget->RemoveFromViewport();
        CurrentVignetteWidget = nullptr;
    }
}
