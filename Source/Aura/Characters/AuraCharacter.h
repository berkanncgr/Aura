

#pragma once

#include "CoreMinimal.h"
#include "AuraCharacterBase.h"
#include "AuraCharacter.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API AAuraCharacter : public AAuraCharacterBase
{
	GENERATED_BODY()

public:

	AAuraCharacter();

	virtual void PossessedBy(AController* NewController) override;
	virtual void InitAbilityActorInfo() override;
	virtual void OnRep_PlayerState() override;
	virtual int32 GetPlayerLevel() override;
	
protected:

	
	
	
};
