


#include "AuraAbilitySystemComponent.h"

#include "Kismet/KismetSystemLibrary.h"

void UAuraAbilitySystemComponent::AbilityActorInfoSet()
{
	OnGameplayEffectAppliedDelegateToSelf.AddUObject(this,&UAuraAbilitySystemComponent::EffectApplied);
}

void UAuraAbilitySystemComponent::EffectApplied(UAbilitySystemComponent* AbilitySystemComponent, const FGameplayEffectSpec& EffectSpec, FActiveGameplayEffectHandle ActiveEffectHandle)
{
	//UKismetSystemLibrary::PrintString(GetWorld(),TEXT("EffectApplied"),1,1,FColor::Red,8);

	// If effect type is instant, GetGrantedTags wont work.
	FGameplayTagContainer TagContainer;
	EffectSpec.GetAllAssetTags(TagContainer);
	EffectAssetTags.Broadcast(TagContainer);

	for(const FGameplayTag& Tag : TagContainer)
	{
		//@todo: Broadcast the Tag to the WidgetController.
		FString M = FString::Printf(TEXT(" Tag: %s"),*Tag.ToString());
		UKismetSystemLibrary::PrintString(GetWorld(),M,1,1,FColor::Red,3);
	}
}
