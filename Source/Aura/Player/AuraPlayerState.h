

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/PlayerState.h"
#include "AuraPlayerState.generated.h"

class UAttributeSet;
/**
 * 
 */
UCLASS()
class AURA_API AAuraPlayerState : public APlayerState, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:

	AAuraPlayerState();

	FORCEINLINE virtual class UAbilitySystemComponent* GetAbilitySystemComponent() const override
	{ return AbilitySystemComponent; }

	FORCEINLINE UAttributeSet* GetAttributeSet() const
	{ return AttributeSet;}

protected:

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TObjectPtr< UAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)

	TObjectPtr<UAttributeSet> AttributeSet;
	
};
