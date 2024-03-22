// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FontManager.generated.h"

UCLASS()
class REDEMPTION_API AFontManager : public AActor
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UFont* EnglishFont;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UFont* KoreanFont;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UFont* PortugueseFont;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UFont* HindiFont;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UFont* GujaratiFont;

public:	
	// Sets default values for this actor's properties
	AFontManager();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFont* GetFonts(FString Lang);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

};
