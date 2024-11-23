
#include "MMC_MaxHealth.h"
#include "Aura/AbilitySystem/AuraAttributeSet.h"
#include "Aura/Interfaces/CombatInterface.h"
#include "Kismet/KismetSystemLibrary.h"

UMMC_MaxHealth::UMMC_MaxHealth()
{
	VigorDef.AttributeToCapture = UAuraAttributeSet::GetVigorAttribute();
	VigorDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Target;
	VigorDef.bSnapshot = false;

	RelevantAttributesToCapture.Add(VigorDef);
}

float UMMC_MaxHealth::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
{
	// Gather tags from source and target:
	const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();

	FAggregatorEvaluateParameters EvaluateParameters;
	EvaluateParameters.SourceTags = SourceTags, EvaluateParameters.TargetTags = TargetTags;

	float VigorValue = 0;
	GetCapturedAttributeMagnitude(VigorDef,Spec,EvaluateParameters,VigorValue);
	VigorValue = FMath::Max<float>(VigorValue,0);

	ICombatInterface* CombatInterface = Cast<ICombatInterface>(Spec.GetContext().GetSourceObject());
	if(!CombatInterface) return 0;
	const int32 PlayerLevel = CombatInterface->GetPlayerLevel();

	return 80.f + (VigorValue * 2.5) +  (10 * PlayerLevel);
}
