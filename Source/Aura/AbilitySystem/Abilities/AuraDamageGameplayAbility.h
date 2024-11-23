

#pragma once

#include "CoreMinimal.h"
#include "Aura/AbilitySystem/Abilities/AuraGameplayAbility.h"
#include "AuraDamageGameplayAbility.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API UAuraDamageGameplayAbility : public UAuraGameplayAbility
{
	GENERATED_BODY()

protected:

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UGameplayEffect> ProjectileDamageEffectClass;
	
	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	TMap<FGameplayTag,FScalableFloat> DamageTypesMap;
	
	
};
