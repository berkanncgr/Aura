

#include "Aura/UI/WidgetControllers/AttributeMeunWidgetController.h"

#include "Aura/AuraGameplayTags.h"
#include "Aura/AbilitySystem/AuraAttributeSet.h"
#include "Aura/AbilitySystem/Data/AttributeInfoDataAsset.h"


void UAttributeMeunWidgetController::BindCallbacksToDependencies()
{
	
}

void UAttributeMeunWidgetController::BroadcastInitialValues()
{
	if(!AttributeInfoDataAsset) return;
	
	UAuraAttributeSet* AS = CastChecked<UAuraAttributeSet>(AttributeSet);
	
	for(auto& Pair : AS->TagsToAttributesMap)
	{
		FAuraAttributeInfo AttributeInfo = AttributeInfoDataAsset->FindAttributeInfoForTag(Pair.Key);
		FGameplayAttribute Attribute = Pair.Value.Execute();
		AttributeInfo.AttributeValue = Attribute.GetNumericValue(AS);
		AttributeInfoSignature.Broadcast(AttributeInfo);
	}
}
