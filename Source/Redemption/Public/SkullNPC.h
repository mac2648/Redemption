// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interface_Dialogue.h"
#include "SkullNPC.generated.h"

class UBoxComponent;
class USkeletalMeshComponent;
class UInteractWidgetComponent;

UCLASS()
class REDEMPTION_API ASkullNPC : public AActor, public IInterface_Dialogue
{
	GENERATED_BODY()
	
protected:

	UPROPERTY(EditAnywhere)
	UInteractWidgetComponent* InteractComp;

	UPROPERTY(EditAnywhere)
	USkeletalMeshComponent* SkullMeshComp;

	UPROPERTY(EditAnywhere, Category = "HUD")
	TSubclassOf<UUserWidget> DialogueWidgetClass;

	UPROPERTY(BlueprintReadOnly)
	UUserWidget* DialogueWidget;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<FText> Dialogues;

	UPROPERTY(BlueprintReadOnly)
	int32 TalkIndex = -1;

	UPROPERTY(EditAnywhere, Category = "Sound")
	USoundBase* XyloSounds;

	FTimerHandle SoundTimerHandle;

private:

	bool IsTalking = false;

public:	
	// Sets default values for this actor's properties
	ASkullNPC();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void PlayNextSound(int32 CurrentSoundIndex, int32 TotalSounds);

	UFUNCTION(BlueprintCallable)
	void OnPlayerDeath();

	virtual void Talk() override;

	void ResetDialogue();

	UFUNCTION(BlueprintCallable)
	bool GetIsTalking() { return IsTalking; }

	UFUNCTION(BlueprintImplementableEvent)
	void SetDialogueText(const FText& Dialogue);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintImplementableEvent)
	void FinishTalk();

};
