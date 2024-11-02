


#include "Aura/AbilitySystem/Data/AttributeInfoDataAsset.h"


FAuraAttributeInfo UAttributeInfoDataAsset::FindAttributeInfoForTag(const FGameplayTag& AttributeTag, bool bLogNotFound) const
{
	for (const FAuraAttributeInfo& Info : AttributeInformation)
	{
		if(Info.AttributeTag.MatchesTagExact(AttributeTag))
		{
			return Info;
		}
	}

	if(bLogNotFound) UE_LOG(LogTemp, Error, TEXT("Attribute not found"));
	return FAuraAttributeInfo();
}
