// Copyright Druid Mechanics


#include "AbilitySystem/Debuff/DebuffNiagaraComponent.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "Interaction/CombatInterface.h"

UDebuffNiagaraComponent::UDebuffNiagaraComponent()
{
	bAutoActivate = false;
	
	static ConstructorHelpers::FObjectFinder<UNiagaraSystem> NiagaraSystemAsset(TEXT("/Game/Assets/Effects/Fire/NS_Fire.NS_Fire"));

	if (NiagaraSystemAsset.Succeeded())
	{
		SetAsset(NiagaraSystemAsset.Object);
	}
}

void UDebuffNiagaraComponent::BeginPlay()
{
	Super::BeginPlay();

	UAbilitySystemComponent* ASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetOwner());
	if (ASC) ASC->RegisterGameplayTagEvent(DebuffTag,EGameplayTagEventType::NewOrRemoved).AddUObject(this,&ThisClass::DebuffTagChanged);

	else
	{
		ICombatInterface* CombatInterface = Cast<ICombatInterface>(GetOwner());
		CombatInterface->GetOnASCRegisteredDelegate().AddWeakLambda(this, [this](UAbilitySystemComponent* InASC)
		{
			InASC->RegisterGameplayTagEvent(DebuffTag, EGameplayTagEventType::NewOrRemoved).AddUObject(this, &UDebuffNiagaraComponent::DebuffTagChanged);
		});
	}
}

void UDebuffNiagaraComponent::DebuffTagChanged(FGameplayTag GameplayTag, int NewCount)
{
	const bool bOwnerAlive = IsValid(GetOwner()) &&  GetOwner()->Implements<UCombatInterface>() && !ICombatInterface::Execute_IsDead(GetOwner());
	if (!bOwnerAlive) return;
	NewCount >0 ? Activate()  : Deactivate();
}
