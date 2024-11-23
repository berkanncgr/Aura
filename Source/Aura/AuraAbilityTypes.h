#pragma once

#include "GameplayEffectTypes.h"
#include "AuraAbilityTypes.Generated.h"

USTRUCT(BlueprintType)
struct FAuraGameplayEffectContext : public FGameplayEffectContext
{
	GENERATED_BODY()

	/** Returns the actual struct used for serialization, subclasses must override this! */
	virtual UScriptStruct* GetScriptStruct() const
	{
		return StaticStruct();
	}

	virtual bool NetSerialize(FArchive& Ar, class UPackageMap* Map, bool& bOutSuccess) override;


	bool GetIsCriticalHit() const { return bIsCriticalHit; }
	bool GetIsBlockedHit() const { return bIsBlockedHit; }

	void SetCriticalHit(bool InIsCriticalHit) { bIsCriticalHit = InIsCriticalHit; }
	void SetBlockedHit(bool InBlockedHit) { bIsBlockedHit = InBlockedHit; }
	
protected:

	UPROPERTY()
	bool bIsBlockedHit = false;

	UPROPERTY()
	bool bIsCriticalHit = false;
	
};

template<>
struct TStructOpsTypeTraits<FAuraGameplayEffectContext>  : public TStructOpsTypeTraitsBase2<FAuraGameplayEffectContext>
{
	enum
	{
		WithNetSerializer = true,
		WithCopy = true
	};
};