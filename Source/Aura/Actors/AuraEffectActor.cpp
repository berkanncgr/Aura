


#include "AuraEffectActor.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "Components/SphereComponent.h"
//#include "AbilitySystemInterface.h"
//#include "Aura/AbilitySystem/AuraAttributeSet.h"

AAuraEffectActor::AAuraEffectActor()
{
	PrimaryActorTick.bCanEverTick = PrimaryActorTick.bAllowTickOnDedicatedServer = PrimaryActorTick.bStartWithTickEnabled = false;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	SetRootComponent(Mesh);
	
	Sphere = CreateDefaultSubobject<USphereComponent>("Sphere");
	Sphere->SetupAttachment(Mesh);
}

void AAuraEffectActor::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	Sphere->OnComponentBeginOverlap.AddDynamic(this,&ThisClass::SphereBeginOverlap);
	Sphere->OnComponentEndOverlap.AddDynamic(this,&AAuraEffectActor::SphereEndOverlap);

}

void AAuraEffectActor::SphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

	/** First attemt to change any attribute. This cna be better with gameplay effects. Will be commented out when gameplayeffects are created. */
	/*
	IAbilitySystemInterface* ASCInterface = Cast<IAbilitySystemInterface>(OtherActor);
	if(!ASCInterface) return;

	const UAttributeSet* AS = ASCInterface->GetAbilitySystemComponent()->GetAttributeSet(UAuraAttributeSet::StaticClass());
	if(!AS) return;
	
	const UAuraAttributeSet* AAS = Cast<UAuraAttributeSet>(AS);
	if(!AAS) return;
	
	UAuraAttributeSet* AuraAttributeSet = const_cast<UAuraAttributeSet*>(AAS);
	AuraAttributeSet->SetMana(AAS->GetMana() + 25);
	AuraAttributeSet->SetHealth(AAS->GetHealth() -20);
	Destroy();
	*/

	if(EffectApplicationPolicy == EEffectApplicationPolicy::OnOverlap)
	ApplyEffectToTarget(OtherActor,GameplayEffectClass);
}


void AAuraEffectActor::ApplyEffectToTarget(AActor* Target, TSubclassOf<UGameplayEffect> EffectToApply)
{
	UAbilitySystemComponent* TargetAsc = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(Target);
	if(!TargetAsc) return; check(EffectToApply);

	FGameplayEffectContextHandle EffectContextHandle = TargetAsc->MakeEffectContext();
	EffectContextHandle.AddSourceObject(this); //What object caused this effect.
	
	const FGameplayEffectSpecHandle EffectSpecHandle = TargetAsc->MakeOutgoingSpec(EffectToApply,EffectLevel,EffectContextHandle);
	// We use this function because ???
	FActiveGameplayEffectHandle ActiveGameplayEffect = TargetAsc->ApplyGameplayEffectSpecToSelf(*EffectSpecHandle.Data.Get());

	// Def is GameplayEffect SELF.
	const EGameplayEffectDurationType Policy = EffectSpecHandle.Data.Get()->Def->DurationPolicy;
	const bool bIsInfinite = Policy == EGameplayEffectDurationType::Infinite;

	if(bIsInfinite && EffectRemovalPolicy == EEffectRemovalPolicy::OnEndOverlap)
		ActiveEffectHandlesMap.Add(ActiveGameplayEffect, TargetAsc);

	if(bShouldDestroyAfterApplyingEffect) Destroy();
}


void AAuraEffectActor::SphereEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int OtherBodyIndex)
{	
	if(EffectApplicationPolicy == EEffectApplicationPolicy::OnEndOverlap)
		ApplyEffectToTarget(OtherActor,GameplayEffectClass);
	

	if(EffectRemovalPolicy == EEffectRemovalPolicy::OnEndOverlap)
		RemoveEffectFromTarget(OtherActor);
}


void AAuraEffectActor::RemoveEffectFromTarget(AActor* Target)
{
	UAbilitySystemComponent* TargetAsc = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(Target);
	if(!TargetAsc) return;
	
	TArray<FActiveGameplayEffectHandle> HandlesToRemove;
	for(auto HandlePair : ActiveEffectHandlesMap)
	{
		if(HandlePair.Value == TargetAsc)
		{
			HandlesToRemove.Add(HandlePair.Key);
			TargetAsc->RemoveActiveGameplayEffect(HandlePair.Key,1);
		}
	}

	for(FActiveGameplayEffectHandle& Handle : HandlesToRemove)
	{
		ActiveEffectHandlesMap.FindAndRemoveChecked(Handle);
	}

	if(bShouldDestroyAfterRemovingEffect) Destroy();
}
