


#include "Aura/Input/AuraInputConfigDataAsset.h"

const UInputAction* UAuraInputConfigDataAsset::FindAbilityInputActionForTag(const FGameplayTag& InputTag, bool bLogNotFound) const
{
	for(const auto& Action  : AbilityInputActions)
	{
		if(!Action.InputAction) continue;
		if(Action.InputTag == InputTag) return Action.InputAction;
	}

	if(bLogNotFound)
	{
		UE_LOG(LogTemp, Error, TEXT(" Input could NOT found. Tag: %s"),*InputTag.ToString());
	}

	return nullptr;
}
