#pragma once

#include "CoreMinimal.h"
#include "Kismet/GameplayStatics.h"

namespace RedemptionUtils
{
	template <class ComponentT>
	void GetAllActorsWithComponentByClass(UWorld* WorldContextObject,TArray<AActor*> &OutActors)
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
}