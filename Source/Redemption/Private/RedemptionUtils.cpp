#include "RedemptionUtils.h"

namespace RedemptionUtils
{
	int32 GetWorldID(UWorld* WorldContextObject)
	{
		FString MapName = WorldContextObject->GetName();
		MapName.RemoveAt(0, 5);
		//Levels need to be called "Level" + the number
		UE_LOG(LogTemp, Warning, TEXT("Level %d"), FCString::Atoi(*MapName));
		UE_LOG(LogTemp, Warning, TEXT("MapName = %s"), *MapName);
		return FCString::Atoi(*MapName) - 1;
	}
}