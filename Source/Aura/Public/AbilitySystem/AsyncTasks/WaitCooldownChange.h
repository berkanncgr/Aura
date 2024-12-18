// Copyright Druid Mechanics

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "WaitCooldownChange.generated.h"

struct FGameplayTag;
class UAbilitySystemComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FCoolDownChangeSignature, float, TimeRemaining);

UCLASS(BlueprintType, meta=(ExposedAsyncProxy = "AsyncTask"))
class AURA_API UWaitCooldownChange : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintAssignable)
	FCoolDownChangeSignature CooldownStart;

	UPROPERTY(BlueprintAssignable)
	FCoolDownChangeSignature CooldownEnd;
	
	UFUNCTION(BlueprintCallable,meta= (BlueprintInternalUseOnly=true))
	static UWaitCooldownChange* WaitForCooldownChange(UAbilitySystemComponent* AbilitySystemComponent, const FGameplayTag& InCooldownTag);

	UFUNCTION(BlueprintCallable)
	void EndTask();

protected:

	UPROPERTY()
	UAbilitySystemComponent* ASC;

	FGameplayTag CooldownTag;


	UFUNCTION()
	void CooldownTagChanged(const FGameplayTag InCooldownTag, int32 NewCount);

	UFUNCTION()
	void OnActiveEffectAdded(UAbilitySystemComponent* TargetASC, const FGameplayEffectSpec& AppliedSpec, FActiveGameplayEffectHandle ActiveGameplayEffectHandle);
};
