// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "DevTools.h"
#include "RedemptionUtils.generated.h"

/**
 * 
 */
UCLASS()
class REDEMPTION_API URedemptionUtils : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	template <class ComponentT>
	static void GetAllActorsWithComponentByClass(UWorld* WorldContextObject, TArray<AActor*>& OutActors)
	{
		OutActors.Empty();

		TArray<AActor*> AllActors;

		UGameplayStatics::GetAllActorsOfClass(WorldContextObject, AActor::StaticClass(), AllActors);

		for (AActor* Current : AllActors)
		{
			if (Current->GetComponentByClass<ComponentT>())
			{
				OutActors.Add(Current);
			}
		}
	}

	UFUNCTION(BlueprintCallable)
	static int32 GetWorldID(UWorld* WorldContextObject);
};
