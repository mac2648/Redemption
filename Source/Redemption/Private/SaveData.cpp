#include "SaveData.h"

USaveData::USaveData()
{
	for (int i = 0; i < NUM_LEVELS; i++)
	{
		SaveDataStruct.PlayerDiedLocation.Add(FVector::ZeroVector);
		SaveDataStruct.CompletedLevels.Add(false);
	}
}

