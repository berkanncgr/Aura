
#include "AuraAbilitySystemComponent.h"

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
}
