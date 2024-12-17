// Copyright Druid Mechanics


#include "AbilitySystem/AsyncTasks/WaitCooldownChange.h"

#include "AbilitySystemComponent.h"
#include "Kismet/KismetSystemLibrary.h"

UWaitCooldownChange* UWaitCooldownChange::WaitForCooldownChange(UAbilitySystemComponent* AbilitySystemComponent, const FGameplayTag& InCooldownTag)
{
	UWaitCooldownChange* Obj = NewObject<UWaitCooldownChange>();
	Obj->ASC = AbilitySystemComponent;
	Obj->CooldownTag = InCooldownTag;

	if (!IsValid(AbilitySystemComponent) || !InCooldownTag.IsValid())
	{
		Obj->EndTask();
		return nullptr;
	}

	AbilitySystemComponent->OnActiveGameplayEffectAddedDelegateToSelf.AddUObject(Obj,&ThisClass::OnActiveEffectAdded);
	AbilitySystemComponent->RegisterGameplayTagEvent(InCooldownTag,EGameplayTagEventType::NewOrRemoved).AddUObject(Obj,&UWaitCooldownChange::CooldownTagChanged);
	return Obj;
}


void UWaitCooldownChange::CooldownTagChanged(const FGameplayTag InCooldownTag, int32 NewCount)
{
	if (NewCount == 0) CooldownEnd.Broadcast(0);
}

void UWaitCooldownChange::OnActiveEffectAdded(UAbilitySystemComponent* TargetASC, const FGameplayEffectSpec& AppliedSpec, FActiveGameplayEffectHandle ActiveGameplayEffectHandle)
{
	FGameplayTagContainer AssetTags;
	AppliedSpec.GetAllAssetTags(AssetTags);

	FGameplayTagContainer GrantedTags;
	AppliedSpec.GetAllBlockedAbilityTags(GrantedTags);

	if (AssetTags.HasTagExact(CooldownTag) || GrantedTags.HasTagExact(CooldownTag))
	{
		FGameplayEffectQuery EffectQuery = FGameplayEffectQuery::MakeQuery_MatchAnyOwningTags(CooldownTag.GetSingleTagContainer());
		
		TArray<float> Array = ASC->GetActiveEffectsTimeRemaining(EffectQuery);
		if (Array.Num() > 0)
		{
			float TimeRemaining = Array[0];
			for (int32 i = 0; i < Array.Num(); i++)
			{
				if (Array[i] > TimeRemaining)
				{
					TimeRemaining = Array[i];
				}
			}
			
			CooldownStart.Broadcast(TimeRemaining);
			UKismetSystemLibrary::PrintString(GetWorld(),TEXT("COOLDOWN START"),1,1,FColor::Red,2);
		}
	}
}

void UWaitCooldownChange::EndTask()
{
	if (!IsValid(ASC)) return;
	ASC->RegisterGameplayTagEvent(CooldownTag,EGameplayTagEventType::NewOrRemoved).RemoveAll(this);
	SetReadyToDestroy();
	MarkAsGarbage();
}
