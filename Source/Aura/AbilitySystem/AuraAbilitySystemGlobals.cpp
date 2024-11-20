

#include "Aura/AbilitySystem/AuraAbilitySystemGlobals.h"
#include "Aura/AuraAbilityTypes.h"

FGameplayEffectContext* UAuraAbilitySystemGlobals::AllocGameplayEffectContext() const
{
	return new FAuraGameplayEffectContext();
}
