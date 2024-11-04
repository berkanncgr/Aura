

#include "Aura/UI/WidgetControllers/AttributeMeunWidgetController.h"

#include "Aura/AuraGameplayTags.h"
#include "Aura/AbilitySystem/AuraAttributeSet.h"
#include "Aura/AbilitySystem/Data/AttributeInfoDataAsset.h"


void UAttributeMeunWidgetController::BindCallbacksToDependencies()
{
	UAuraAttributeSet* AS = CastChecked<UAuraAttributeSet>(AttributeSet);
	
	for(auto& Pair : AS->TagsToAttributesMap)
	{
		FGameplayAttribute Attribute = Pair.Value();
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(Attribute).AddLambda( [this,Pair, AS](const FOnAttributeChangeData& Data)
		{
			BroadcastAttributeInfo(Pair.Key,Pair.Value());
		});

	}
}

void UAttributeMeunWidgetController::BroadcastInitialValues()
{
	if(!AttributeInfoDataAsset) return;
	
	UAuraAttributeSet* AS = CastChecked<UAuraAttributeSet>(AttributeSet);
	
	for(auto& Pair : AS->TagsToAttributesMap)
	{
		BroadcastAttributeInfo(Pair.Key,Pair.Value());
		
		// Old usage:
		/*FAuraAttributeInfo AttributeInfo = AttributeInfoDataAsset->FindAttributeInfoForTag(Pair.Key);
		FGameplayAttribute Attribute = Pair.Value(); // Value is a function pointer, so Value() is syntax.
		AttributeInfo.AttributeValue = Attribute.GetNumericValue(AS);
		AttributeInfoSignature.Broadcast(AttributeInfo);*/

	}
}

void UAttributeMeunWidgetController::BroadcastAttributeInfo(const FGameplayTag& AttributeTag,const FGameplayAttribute& Attribute) const
{
	FAuraAttributeInfo AttributeInfo = AttributeInfoDataAsset->FindAttributeInfoForTag(AttributeTag);
	AttributeInfo.AttributeValue = Attribute.GetNumericValue(AttributeSet);
	AttributeInfoSignature.Broadcast(AttributeInfo);
}
