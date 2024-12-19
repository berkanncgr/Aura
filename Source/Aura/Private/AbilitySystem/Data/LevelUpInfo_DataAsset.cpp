// Copyright Druid Mechanics


#include "AbilitySystem/Data/LevelUpInfo_DataAsset.h"

int32 ULevelUpInfo_DataAsset::FindLevelForXP(int32 XP)
{
	int32 Level = 1;
	bool bSearching = true;
	while (bSearching)
	{
		if (LevelUpInformation.Num() - 1 <= Level) return Level;
		(XP >= LevelUpInformation[Level].LevelUpRequirement) ? ++Level : bSearching = false;

	}
	return Level;
}
