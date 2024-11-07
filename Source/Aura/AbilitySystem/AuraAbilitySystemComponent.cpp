
#include "AuraAbilitySystemComponent.h"

#include "Abilities/AuraGameplayAbility.h"
#include "Aura/AuraGameplayTags.h"
#include "Kismet/KismetSystemLibrary.h"


void UAuraAbilitySystemComponent::AbilityActorInfoSet()
{
	OnGameplayEffectAppliedDelegateToSelf.AddUObject(this,&UAuraAbilitySystemComponent::EffectApplied);

	/* // Accessing any tag example: 
	const auto& GameplayTags = FAuraGameplayTags::Get();
	GameplayTags.Attributes_Primary_Intelligence; */
}

void UAuraAbilitySystemComponent::EffectApplied(UAbilitySystemComponent* AbilitySystemComponent, const FGameplayEffectSpec& EffectSpec, FActiveGameplayEffectHandle ActiveEffectHandle)
{
	UKismetSystemLibrary::PrintString(GetWorld(),TEXT("EffectApplied"),1,1,FColor::Red,8);

	// If effect type is instant, GetGrantedTags wont work.
	FGameplayTagContainer TagContainer;
	EffectSpec.GetAllAssetTags(TagContainer);
	EffectAssetTags.Broadcast(TagContainer);

	Client_EffectApplied(AbilitySystemComponent,EffectSpec,ActiveEffectHandle);
}

void UAuraAbilitySystemComponent::Client_EffectApplied_Implementation(UAbilitySystemComponent* AbilitySystemComponent, const FGameplayEffectSpec& EffectSpec, FActiveGameplayEffectHandle ActiveEffectHandle)
{
	UKismetSystemLibrary::PrintString(GetWorld(),TEXT("EffectApplied"),1,1,FColor::Red,8);

	// If effect type is instant, GetGrantedTags wont work.
	FGameplayTagContainer TagContainer;
	EffectSpec.GetAllAssetTags(TagContainer);
	EffectAssetTags.Broadcast(TagContainer);
}


void UAuraAbilitySystemComponent::AddCharacterAbilities(const TArray<TSubclassOf<UGameplayAbility>>& StartupAbilities)
{
	for(TSubclassOf<UGameplayAbility> AbilityClass:StartupAbilities)
	{
		FGameplayAbilitySpec AbilitySpec = FGameplayAbilitySpec(AbilityClass,1);

		const UAuraGameplayAbility* AuraAbility = Cast<UAuraGameplayAbility>(AbilitySpec.Ability);
		AbilitySpec.DynamicAbilityTags.AddTag(AuraAbility->StartupInputTag);
		GiveAbility(AbilitySpec);
		//GiveAbilityAndActivateOnce(AbilitySpec);
	}
}

void UAuraAbilitySystemComponent::AbilityInputTagHeld(const FGameplayTag& InputTag)
{
	if(!InputTag.IsValid()) return;

	TArray<FGameplayAbilitySpec> ActiveAbilities = GetActivatableAbilities();
	
	for(FGameplayAbilitySpec AbilitySpec : ActiveAbilities)
	{
		if(!AbilitySpec.DynamicAbilityTags.HasTagExact(InputTag)) continue;

		AbilitySpecInputPressed(AbilitySpec);
		if(!AbilitySpec.IsActive())
		{
			TryActivateAbility(AbilitySpec.Handle);
		}
	}
}

void UAuraAbilitySystemComponent::AbilityInputTagReleased(const FGameplayTag& InputTag)
{
	if(!InputTag.IsValid()) return;
	

	for(FGameplayAbilitySpec AbilitySpec : GetActivatableAbilities())
	{
		if(!AbilitySpec.DynamicAbilityTags.HasTagExact(InputTag)) continue;
		AbilitySpecInputReleased(AbilitySpec);
	}
}