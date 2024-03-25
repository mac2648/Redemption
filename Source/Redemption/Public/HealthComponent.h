// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Math/Vector.h"
#include "HealthComponent.generated.h"

class UWidgetComponent;

namespace defs
{
	FVector const HealthBarZ{ 0.f, 0.f, 95.f };
}



UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class REDEMPTION_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

private:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UUserWidget> GameOverWidgetClass;

	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<UUserWidget> VignetteWidgetClass;

	float const MaxHealth{ 2.f };
	float Health;
	UUserWidget* CurrentVignetteWidget = nullptr;

	bool IsInvunerable = false;

public:	
	float GetHealth() const;
	float GetMaxHealth() const;
	void SetHealth(float const NewHealth);
	void Die();
	void ResetInvunerability() { IsInvunerable = false; }

	UFUNCTION(BlueprintCallable)
	void GameOver();

	UFUNCTION()
	void TakeDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser);

	UHealthComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
		
};
