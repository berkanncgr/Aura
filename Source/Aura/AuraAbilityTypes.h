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

	virtual bool NetSerialize(FArchive& Ar, class UPackageMap* Map, bool& bOutSuccess) override
	{
		uint32 RepBits = 0;
		if(Ar.IsSaving())
		{
			if (bReplicateInstigator && Instigator.IsValid()) RepBits |= 1 << 0;
			if (bReplicateEffectCauser && EffectCauser.IsValid() ) RepBits |= 1 << 1;
			if (AbilityCDO.IsValid()) RepBits |= 1 << 2;
			if (bReplicateSourceObject && SourceObject.IsValid()) RepBits |= 1 << 3;
			if (Actors.Num() > 0) RepBits |= 1 << 4;
			if (HitResult.IsValid()) RepBits |= 1 << 5;
			if (bHasWorldOrigin) RepBits |= 1 << 6;
			if(bIsBlockedHit) RepBits |= 1<<7;
			if(bIsCriticalHit) RepBits |= 1 << 8;
		
			Ar.Serialize(&RepBits,9);

			if (RepBits & (1 << 0)) Ar << Instigator;
			if (RepBits & (1 << 1)) Ar << EffectCauser;
			if (RepBits & (1 << 2)) Ar << AbilityCDO;
			if (RepBits & (1 << 3)) Ar << SourceObject;
			if (RepBits & (1 << 4)) SafeNetSerializeTArray_Default<31>(Ar, Actors);
		
			if (RepBits & (1 << 5))
			{
				if (Ar.IsLoading())
				{
					if (!HitResult.IsValid()) HitResult = TSharedPtr<FHitResult>(new FHitResult());
				}
				HitResult->NetSerialize(Ar, Map, bOutSuccess);
			}
		
			if (RepBits & (1 << 6))
			{
				Ar << WorldOrigin;
				bHasWorldOrigin = true;
			}
			else  bHasWorldOrigin = false;
		
			if(RepBits & (1 << 7)) Ar<<bIsBlockedHit;
			if(RepBits & (1 << 8)) Ar<<bIsCriticalHit;
		}

		if (Ar.IsLoading()) AddInstigator(Instigator.Get(), EffectCauser.Get()); // Just to initialize InstigatorAbilitySystemComponent
	
		bOutSuccess = true;
		return true;
	}

	/** Creates a copy of this context, used to duplicate for later modifications */
	virtual FAuraGameplayEffectContext* Duplicate() const
	{
		FAuraGameplayEffectContext* NewContext = new FAuraGameplayEffectContext();
		*NewContext = *this;
		if (GetHitResult())
		{
			// Does a deep copy of the hit result
			NewContext->AddHitResult(*GetHitResult(), true);
		}
		return NewContext;
	}

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