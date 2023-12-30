


#include "OverlayWidgetController.h"

#include "Aura/AbilitySystem/AuraAbilitySystemComponent.h"
#include "Aura/AbilitySystem/AuraAttributeSet.h"
#include "Kismet/KismetSystemLibrary.h"

void UOverlayWidgetController::BroadcastInitialValues()
{
	const UAuraAttributeSet* AS = Cast<UAuraAttributeSet>(AttributeSet);
	OnHealthChanged.Broadcast(AS->GetHealth());
	OnMaxHealthChanged.Broadcast(AS->GetMaxHealth());
	OnManaChanged.Broadcast(AS->GetMana());
	OnMaxManaChanged.Broadcast(AS->GetMaxMana());
}

void UOverlayWidgetController::BindCallbacksToDependencies()
{
	const UAuraAttributeSet* AS = Cast<UAuraAttributeSet>(AttributeSet);
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AS->GetHealthAttribute()).AddLambda([this](const FOnAttributeChangeData& Data)
	{ OnHealthChanged.Broadcast(Data.NewValue); } );
	
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AS->GetMaxHealthAttribute()).AddLambda([this](const FOnAttributeChangeData& Data)
	{ OnMaxHealthChanged.Broadcast(Data.NewValue); } );
	
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AS->GetManaAttribute()).AddLambda([this](const FOnAttributeChangeData& Data)
	{ OnManaChanged.Broadcast(Data.NewValue); } );
	
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AS->GetMaxManaAttribute()).AddLambda([this](const FOnAttributeChangeData& Data)
	{ OnMaxManaChanged.Broadcast(Data.NewValue); } );

	UAuraAbilitySystemComponent* AuraAS = Cast<UAuraAbilitySystemComponent>(AbilitySystemComponent);
	AuraAS->EffectAssetTags.AddLambda([this](const FGameplayTagContainer& AssetTags)
	{
		for (const FGameplayTag& Tag: AssetTags)
		{
			if(!Tag.MatchesTag(FGameplayTag::RequestGameplayTag(FName("Message")))) continue;
			UKismetSystemLibrary::PrintString(GetWorld(),FString::Printf(TEXT("TAG: %s"),*Tag.ToString()));
			const FUIWidgetRow* Row = GetDataTableRowByTag<FUIWidgetRow>(MessageWidgetDataTable,Tag);
			if(!Row) continue;
			UKismetSystemLibrary::PrintString(GetWorld(),FString::Printf(TEXT("Founded TAG: %s"),*Tag.ToString()));
			MessageWidgetRowDelegate.Broadcast(*Row);
		}
	});
}