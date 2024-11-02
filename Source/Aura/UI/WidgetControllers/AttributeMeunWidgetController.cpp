

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

	FAuraAttributeInfo VigorInfo =  AttributeInfoDataAsset->FindAttributeInfoForTag(FAuraGameplayTags::Get().Attributes_Primary_Vigor);
	VigorInfo.AttributeValue = AS->GetVigor();
	AttributeInfoSignature.Broadcast(VigorInfo);

	FAuraAttributeInfo StrInfo =  AttributeInfoDataAsset->FindAttributeInfoForTag(FAuraGameplayTags::Get().Attributes_Primary_Strength);
	StrInfo.AttributeValue = AS->GetStrength();
	AttributeInfoSignature.Broadcast(StrInfo);

	FAuraAttributeInfo IntelligenceInfo =  AttributeInfoDataAsset->FindAttributeInfoForTag(FAuraGameplayTags::Get().Attributes_Primary_Intelligence);
	IntelligenceInfo.AttributeValue = AS->GetIntelligence();
	AttributeInfoSignature.Broadcast(IntelligenceInfo);

	FAuraAttributeInfo ResilienceInfo =  AttributeInfoDataAsset->FindAttributeInfoForTag(FAuraGameplayTags::Get().Attributes_Primary_Resilience);
	ResilienceInfo.AttributeValue = AS->GetResilience();
	AttributeInfoSignature.Broadcast(ResilienceInfo);
}
