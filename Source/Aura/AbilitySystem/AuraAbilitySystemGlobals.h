

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemGlobals.h"
#include "AuraAbilitySystemGlobals.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API UAuraAbilitySystemGlobals : public UAbilitySystemGlobals
{
	GENERATED_BODY()

public:

	/** Tell the engine that we are going to use our custom effect context. */
	virtual FGameplayEffectContext* AllocGameplayEffectContext() const override;
	
};
