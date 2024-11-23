
#include "Aura/AbilitySystem/ExecCalcs/ExecCalc_Damage.h"
#include "AbilitySystemComponent.h"
#include "Aura/AuraAbilityTypes.h"
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
	DECLARE_ATTRIBUTE_CAPTUREDEF(ArcaneResistance);
	DECLARE_ATTRIBUTE_CAPTUREDEF(FireResistance);
	DECLARE_ATTRIBUTE_CAPTUREDEF(LightningResistance);
	DECLARE_ATTRIBUTE_CAPTUREDEF(PhysicalResistance);

	TMap<FGameplayTag, FGameplayEffectAttributeCaptureDefinition> TagsToCaptureDefs;
	
	AuraDamageStatics()
	{
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet,Armor,Target,false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet,ArmorPenetration,Source,false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet,BlockChance,Target,false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet,CriticalHitChance,Source,false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet,CriticalHitResistance,Target,false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet,CriticalHitDamage,Source,false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet,ArcaneResistance,Target,false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet,FireResistance,Target,false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet,LightningResistance,Target,false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet,PhysicalResistance,Target,false);

		const FAuraGameplayTags& Tags = FAuraGameplayTags::Get();
		TagsToCaptureDefs.Add(Tags.Attributes_Secondary_Armor, ArmorDef);
		TagsToCaptureDefs.Add(Tags.Attributes_Secondary_BlockChance, BlockChanceDef);
		TagsToCaptureDefs.Add(Tags.Attributes_Secondary_ArmorPenetration, ArmorPenetrationDef);
		TagsToCaptureDefs.Add(Tags.Attributes_Secondary_CriticalHitChance, CriticalHitChanceDef);
		TagsToCaptureDefs.Add(Tags.Attributes_Secondary_CriticalHitResistance, CriticalHitResistanceDef);
		TagsToCaptureDefs.Add(Tags.Attributes_Secondary_CriticalHitDamage, CriticalHitDamageDef);
		TagsToCaptureDefs.Add(Tags.Attributes_Resistance_Arcane, ArcaneResistanceDef);
		TagsToCaptureDefs.Add(Tags.Attributes_Resistance_Fire, FireResistanceDef);
		TagsToCaptureDefs.Add(Tags.Attributes_Resistance_Lightning, LightningResistanceDef);
		TagsToCaptureDefs.Add(Tags.Attributes_Resistance_Physical, PhysicalResistanceDef);
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
	RelevantAttributesToCapture.Add(DamageStatics().ArcaneResistanceDef);
	RelevantAttributesToCapture.Add(DamageStatics().FireResistanceDef);
	RelevantAttributesToCapture.Add(DamageStatics().LightningResistanceDef);
	RelevantAttributesToCapture.Add(DamageStatics().PhysicalResistanceDef);

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
	float Damage = 0;
	for(const TTuple<FGameplayTag,FGameplayTag>& Pair : FAuraGameplayTags::Get().DamageTypesToResistances)
	{
		const FGameplayTag DamageType = Pair.Key;
		const FGameplayTag ResistanceTag = Pair.Value;
		checkf(AuraDamageStatics().TagsToCaptureDefs.Contains(ResistanceTag),TEXT("TagsToCaptureDef does NOT contain Tag [%s] in ExecCalc_Damage"),*ResistanceTag.ToString());
		const FGameplayEffectAttributeCaptureDefinition CaptureDef = AuraDamageStatics().TagsToCaptureDefs[ResistanceTag];

		float Resistance = 0.f;
		ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(CaptureDef,EvaluateParams,Resistance);
		Resistance = FMath::Clamp(Resistance,0.f,100);

		float DamageTypeValue =  EffectSpec.GetSetByCallerMagnitude(Pair.Key,false);
		DamageTypeValue *= (100 - Resistance) / 100;
		Damage+=DamageTypeValue;
	}

	// We captured any attribute we want from who we want to give damage (Target).
	float TargetBlockChance = 0, TargetArmor = 0, SourceArmorPenetration = 0, SourceCriticalHitChance = 0, TargetCriticalHitResistance = 0, SourceCriticalHitDamage = 0;
	
	if(bUseStaticAttributeCapture)
	{
		ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().BlockChanceDef,EvaluateParams,TargetBlockChance);
		ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().ArmorDef,EvaluateParams,TargetArmor);
		ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().ArmorPenetrationDef,EvaluateParams,SourceArmorPenetration);
		ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().CriticalHitChanceDef,EvaluateParams,SourceCriticalHitChance);
		ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().CriticalHitResistanceDef,EvaluateParams,TargetCriticalHitResistance);
		ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().CriticalHitDamageDef,EvaluateParams,SourceCriticalHitDamage);
	}

	else  // Actually we can access the attributes like down below. Why we tried capture attributes? (Maybe tag dependent calculations)
	{
		const UAuraAttributeSet* TargetAS = Cast<UAuraAttributeSet>(TargetASC->GetAttributeSet(UAuraAttributeSet::StaticClass()));
		TargetBlockChance = TargetAS->GetBlockChance();
		TargetArmor = TargetAS->GetArmor();
		TargetCriticalHitResistance = TargetAS->GetCriticalHitResistance();
		
		const UAuraAttributeSet* SourceAS = Cast<UAuraAttributeSet>(SourceASC->GetAttributeSet(UAuraAttributeSet::StaticClass()));
		SourceArmorPenetration = SourceAS->GetArmorPenetration();
		SourceCriticalHitChance = SourceAS->GetCriticalHitChance();
		SourceCriticalHitDamage = SourceAS->GetCriticalHitDamage();
	}

	// If Block, halve the Damage:
	const bool bIsBlocked = FMath::RandRange(1,100) < TargetBlockChance;
	if(bIsBlocked) Damage /= 2;

	FGameplayEffectContextHandle ContextHandle =  EffectSpec.GetContext();
	UAuraAbilitySystemLibrary::SetIsBlockedHit(ContextHandle,bIsBlocked);

	// ArmorPenetration ignores percentage of Target's Armor
	UCurveTable* DamageCoefficientsTable = UAuraAbilitySystemLibrary::GetDamageCoefficientsCurve(SourceCombatInterface->_getUObject());
	const FRealCurve* ArmorPenetrationCurve = DamageCoefficientsTable->FindCurve(FName("ArmorPenetration"),"");
	const float ArmorPenetrationCoefficient = ArmorPenetrationCurve->Eval(SourceCombatInterface->GetPlayerLevel());
	const float EffectiveArmor = TargetArmor *= (100 - (SourceArmorPenetration * ArmorPenetrationCoefficient)) / 100;

	const FRealCurve* EffectiveArmorCurve = DamageCoefficientsTable->FindCurve(FName("EffectiveArmor"),"");
	const float EffectiveArmorCoefficient = EffectiveArmorCurve->Eval(TargetCombatInterface->GetPlayerLevel());
	Damage *= (100- EffectiveArmor * EffectiveArmorCoefficient) / 100;
	
	UCurveTable* CriticalHitCoefficientsTable = UAuraAbilitySystemLibrary::GetDamageCoefficientsCurve(SourceCombatInterface->_getUObject());
	const FRealCurve* CriticalHitCurve = CriticalHitCoefficientsTable->FindCurve(FName("CriticalHitResistance"),"");
	float CriticalHitCoefficient = CriticalHitCurve->Eval(SourceCombatInterface->GetPlayerLevel());
	const float EffectiveCriticalHitChance = SourceCriticalHitChance - TargetCriticalHitResistance * CriticalHitCoefficient;
	const bool bCriticalHit = FMath::RandRange(1,100) < EffectiveCriticalHitChance;
	Damage = bCriticalHit ? Damage*2 + SourceCriticalHitDamage : Damage;
	UAuraAbilitySystemLibrary::SetIsCriticalHit(ContextHandle,bCriticalHit);
	
	const FGameplayModifierEvaluatedData EvaluatedData (UAuraAttributeSet::GetIncomingDamageAttribute(),EGameplayModOp::Additive,Damage);
	OutExecutionOutput.AddOutputModifier(EvaluatedData);
}