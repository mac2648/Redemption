// Fill out your copyright notice in the Description page of Project Settings.


#include "FontManager.h"

// Sets default values
AFontManager::AFontManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AFontManager::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFontManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

UFont* AFontManager::GetFonts(FString Lang)
{
	if (Lang == "en")
	{
		return EnglishFont;
	}
	else if (Lang == "ko")
	{
		return KoreanFont;
	}
	else if (Lang == "pt")
	{
		return PortugueseFont;
	}
	else if (Lang == "hi")
	{
		return HindiFont;
	}
	else if (Lang == "gu")
	{
		return GujaratiFont;
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("There is no language you want."));
		return nullptr;
	}
}

