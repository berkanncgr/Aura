

#include "Aura/AbilitySystem/AuraAbilitySystemGlobals.h"
#include "Aura/AuraAbilityTypes.h"


FGameplayEffectContext* UAuraAbilitySystemGlobals::AllocGameplayEffectContext() const
{
	//return Super::AllocGameplayEffectContext();
	return new FAuraGameplayEffectContext();
}

