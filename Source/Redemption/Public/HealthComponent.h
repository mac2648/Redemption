// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Math/Vector.h"
#include "HealthBarWidget.h"
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
	class UWidgetComponent* WidgetComponent;
	float const MaxHealth{ 100.f };
	float Health;

public:	
	// Sets default values for this component's properties


	float GetHealth() const;
	float GetMaxHealth() const;
	void SetHealth(float const NewHealth);
	void Die();
	void Respawn();

	UFUNCTION(BlueprintCallable)
	void GameOver();

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UUserWidget> GameOverWidgetClass;

	UFUNCTION()
	void TakeDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser);

	UWidgetComponent* GetWidgetComp() { return WidgetComponent; }

	UHealthComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
		
};
