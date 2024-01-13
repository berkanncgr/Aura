

#pragma once

#include "CoreMinimal.h"
#include "Aura/Interfaces/CharacterInterface.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "AuraCharacterBase.generated.h"

class UGameplayEffect;
class UAttributeSet;

UCLASS(Abstract)
class AURA_API AAuraCharacterBase : public ACharacter, public ICharacterInterface,public IAbilitySystemInterface
{
	GENERATED_BODY()

public:

	AAuraCharacterBase();

	virtual AActor* GetSelfAsActor() override;
	
	FORCEINLINE virtual UPawnMovementComponent* GetMovementCompFomInterface() override
	{ return GetMovementComponent();}

	FORCEINLINE virtual  UAbilitySystemComponent* GetAbilitySystemComponent() const override
	{ return AbilitySystemComponent; }

	FORCEINLINE UAttributeSet* GetAttributeSet() const
	{ return AttributeSet;}

protected:
	
	virtual void BeginPlay() override;
	virtual void InitAbilityActorInfo(){};

	virtual void InitializeDefaultAttributes();
	virtual void ApplyEffectToSelf(TSubclassOf<UGameplayEffect> GameplayEffectClass,float Level);
	
	UPROPERTY(EditAnywhere,Category=Combat)
	TObjectPtr<USkeletalMeshComponent> Weapon;

	UPROPERTY()
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY()
	TObjectPtr<UAttributeSet> AttributeSet;

	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	TSubclassOf<UGameplayEffect> DefaultPrimaryAttributes;

	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	TSubclassOf<UGameplayEffect> DefaultSecondaryAttributes;
	
};
