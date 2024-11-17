
#include "Aura/AbilitySystem/ExecCalcs/ExecCalc_Damage.h"
#include "AbilitySystemComponent.h"
#include "Aura/AuraGameplayTags.h"
#include "Aura/AbilitySystem/AuraAbilitySystemLibrary.h"
#include "Aura/AbilitySystem/AuraAttributeSet.h"
#include "Aura/Interfaces/CombatInterface.h"


struct AuraDamageStatics
{
	DECLARE_ATTRIBUTE_CAPTUREDEF(Armor);
	DECLARE_ATTRIBUTE_CAPTUREDEF(ArmorPenetration);
	DECLARE_ATTRIBUTE_CAPTUREDEF(BlockChance);
	DECLARE_ATTRIBUTE_CAPTUREDEF(CriticalHitChance);
	DECLARE_ATTRIBUTE_CAPTUREDEF(CriticalHitResistance);
	DECLARE_ATTRIBUTE_CAPTUREDEF(CriticalHitDamage);
	
	AuraDamageStatics()
	{
		// We want Armor attribute of the TARGET without snapshot (false)
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet,Armor,Target,false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet,ArmorPenetration,Source,false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet,BlockChance,Target,false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet,CriticalHitChance,Source,false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet,CriticalHitResistance,Target,false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet,CriticalHitDamage,Source,false);


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
	RelevantAttributesToCapture.Add(DamageStatics().CriticalHitChanceDef);
	RelevantAttributesToCapture.Add(DamageStatics().CriticalHitResistanceDef);
	RelevantAttributesToCapture.Add(DamageStatics().CriticalHitDamageDef);
}

void UExecCalc_Damage::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams,FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{

	const UAbilitySystemComponent* TargetASC = ExecutionParams.GetTargetAbilitySystemComponent();
	ICombatInterface* TargetCombatInterface = Cast<ICombatInterface>(TargetASC->GetAvatarActor());

	const UAbilitySystemComponent* SourceASC = ExecutionParams.GetSourceAbilitySystemComponent();
	ICombatInterface* SourceCombatInterface = Cast<ICombatInterface>(SourceASC->GetAvatarActor());
	
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

	else  // Actually we can access the attributes like down below. Why we tried capture attributes? (Maybe tag dependent calculations)
	{
		const UAuraAttributeSet* TargetAS = Cast<UAuraAttributeSet>(TargetASC->GetAttributeSet(UAuraAttributeSet::StaticClass()));
		TargetBlockChance = TargetAS->GetBlockChance();
		TargetArmor = TargetAS->GetArmor();
		
		const UAuraAttributeSet* SourceAS = Cast<UAuraAttributeSet>(SourceASC->GetAttributeSet(UAuraAttributeSet::StaticClass()));
		SourceArmorPenetration = SourceAS->GetArmorPenetration();
	}

	// If Block, halve the Damage:
	const bool bIsBlocked = FMath::RandRange(1,100) < TargetBlockChance;
	if(bIsBlocked) Damage /= 2;

	UCurveTable* DamageCoefficientsTable = UAuraAbilitySystemLibrary::GetDamageCoefficientsCurve(SourceCombatInterface->_getUObject());
	const FRealCurve* ArmorPenetrationCurve = DamageCoefficientsTable->FindCurve(FName("ArmorPenetration"),"");
	const float ArmorPenetrationCoefficient = ArmorPenetrationCurve->Eval(SourceCombatInterface->GetPlayerLevel());
	
	// ArmorPenetration ignores percentage of Target's Armor
	const float EffectiveArmor = TargetArmor *= (100 - (SourceArmorPenetration * ArmorPenetrationCoefficient)) / 100;

	const FRealCurve* EffectiveArmorCurve = DamageCoefficientsTable->FindCurve(FName("EffectiveArmor"),"");
	const float EffectiveArmorCoefficient = EffectiveArmorCurve->Eval(TargetCombatInterface->GetPlayerLevel());
	
	Damage *= (100- EffectiveArmor * EffectiveArmorCoefficient) / 100;
	const FGameplayModifierEvaluatedData EvaluatedData (UAuraAttributeSet::GetIncomingDamageAttribute(),EGameplayModOp::Additive,Damage);
	OutExecutionOutput.AddOutputModifier(EvaluatedData);
}