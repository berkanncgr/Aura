

#pragma once

#include "CoreMinimal.h"
#include "Aura/Interfaces/CharacterInterface.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "AuraBaseCharacter.generated.h"

class UAttributeSet;

UCLASS(Abstract)
class AURA_API AAuraBaseCharacter : public ACharacter, public ICharacterInterface,public IAbilitySystemInterface
{
	GENERATED_BODY()

public:

	AAuraBaseCharacter();

	virtual AActor* GetSelfAsActor() override;
	
	FORCEINLINE virtual UPawnMovementComponent* GetMovementCompFomInterface() override
	{ return GetMovementComponent();}

	FORCEINLINE virtual  UAbilitySystemComponent* GetAbilitySystemComponent() const override
	{ return AbilitySystemComponent; }

	FORCEINLINE UAttributeSet* GetAttributeSet() const
	{ return AttributeSet;}

protected:
	
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere,Category=Combat)
	TObjectPtr<USkeletalMeshComponent> Weapon;

	UPROPERTY()
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY()
	TObjectPtr<UAttributeSet> AttributeSet;
	
};
