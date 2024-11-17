
#include "Aura/AbilitySystem/ExecCalcs/ExecCalc_Damage.h"
#include "AbilitySystemComponent.h"
#include "Aura/AuraGameplayTags.h"
#include "Aura/AbilitySystem/AuraAttributeSet.h"


struct AuraDamageStatics
{
	DECLARE_ATTRIBUTE_CAPTUREDEF(Armor);
	DECLARE_ATTRIBUTE_CAPTUREDEF(ArmorPenetration);
	DECLARE_ATTRIBUTE_CAPTUREDEF(BlockChance);
	
	AuraDamageStatics()
	{
		// We want Armor attribute of the TARGET without snapshot (false)
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet,Armor,Target,false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet,ArmorPenetration,Source,false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet,BlockChance,Target,false);
	}
};

// Everytime we call this function, we get the same object because it is static.  !!! Return value does not go away when the function ends !!!!
static const AuraDamageStatics& DamageStatics()
{
	static AuraDamageStatics DamageStatics;
	return DamageStatics;
}

UExecCalc_Damage::UExecCalc_Damage()
{
	// ArmorDef came from MACRO In AuraDamageStatics Struct. :)
	RelevantAttributesToCapture.Add(DamageStatics().ArmorDef);
	RelevantAttributesToCapture.Add(DamageStatics().ArmorPenetrationDef);
	RelevantAttributesToCapture.Add(DamageStatics().BlockChanceDef);
}

void UExecCalc_Damage::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams,FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
	const FGameplayEffectSpec EffectSpec = ExecutionParams.GetOwningSpec();

	const FGameplayTagContainer* SourceTags = EffectSpec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* TargetTags = EffectSpec.CapturedTargetTags.GetAggregatedTags();

	FAggregatorEvaluateParameters EvaluateParams;
	EvaluateParams.SourceTags = SourceTags;
	EvaluateParams.TargetTags = TargetTags;

	// Get Damage Set by Caller Magnitude: Damage amount from CT, we captured with correct tag.
	float Damage = EffectSpec.GetSetByCallerMagnitude(FAuraGameplayTags::Get().Damage,false);

	// We captured any attribute we want from who we want to give damage (Target).
	float TargetBlockChance = 0, TargetArmor = 0, SourceArmorPenetration = 0;
	
	if(bUseStaticAttributeCapture)
	{
		ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().BlockChanceDef,EvaluateParams,TargetBlockChance);
		ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().ArmorDef,EvaluateParams,TargetArmor);
		ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().ArmorPenetrationDef,EvaluateParams,SourceArmorPenetration);
	}

	else
	{
		// Actually we can access the attributes this way. Why we tried the capture attributes?
		const UAbilitySystemComponent* TargetASC = ExecutionParams.GetTargetAbilitySystemComponent();
		const UAuraAttributeSet* TargetAS = Cast<UAuraAttributeSet>(TargetASC->GetAttributeSet(UAuraAttributeSet::StaticClass()));
		TargetBlockChance = TargetAS->GetBlockChance();
		TargetArmor = TargetAS->GetArmor();

		const UAbilitySystemComponent* SourceASC = ExecutionParams.GetSourceAbilitySystemComponent();
		const UAuraAttributeSet* SourceAS = Cast<UAuraAttributeSet>(SourceASC->GetAttributeSet(UAuraAttributeSet::StaticClass()));
		SourceArmorPenetration = SourceAS->GetArmorPenetration();
	}

	// If Block, halve the Damage:
	const bool bIsBlocked = FMath::RandRange(1,100) < TargetBlockChance;
	if(bIsBlocked) Damage /= 2;

	// ArmorPenetration ignores percentage of Target's Armor
	const float EffectiveArmor = TargetArmor *= (100 - (SourceArmorPenetration /4)) / 100;
	Damage *= (100- EffectiveArmor * 0.3) / 100;
	
	const FGameplayModifierEvaluatedData EvaluatedData (UAuraAttributeSet::GetIncomingDamageAttribute(),EGameplayModOp::Additive,Damage);
	OutExecutionOutput.AddOutputModifier(EvaluatedData);
}
