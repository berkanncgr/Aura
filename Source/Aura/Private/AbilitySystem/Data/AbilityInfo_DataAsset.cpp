// Copyright Druid Mechanics


#include "AbilitySystem/Data/AbilityInfo_DataAsset.h"

#include "Aura/AuraLogChannels.h"

FAuraAbilityInfo UAbilityInfo_DataAsset::FindAbilityInfoForTag(const FGameplayTag AbilityTag, bool bWarnIfNotFound)
{
	for (const FAuraAbilityInfo& Info : AbilityInformation)
	{
		if (Info.AbilityTag == AbilityTag)
		{
			return Info;
		}
	}

	if (bWarnIfNotFound) UE_LOG(LogAura,Error,TEXT("Ability Tag Not Found {UAbilityInfo_DataAsset::FinAbilityInfoForTag}. Tag: %s"),*AbilityTag.ToString());
	return FAuraAbilityInfo();
}
