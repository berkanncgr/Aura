

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Tasks/AbilityTask.h"
#include "TargetDataUnderMouse.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FMouseTargetDataDelegate, const FGameplayAbilityTargetDataHandle&, DataHandle);

UCLASS()
class AURA_API UTargetDataUnderMouse : public UAbilityTask
{
	GENERATED_BODY()

public:

	/***/
	UFUNCTION(BlueprintCallable,Category="Ability | Tasks",meta=(HidePin = "OwningAbility"),meta=(DefaultToSelf = "OwningAbility"), meta=(BlueprintInternalUseOnly = "true"))
	static UTargetDataUnderMouse* CreateTargetDataUnderMouse(UGameplayAbility* OwningAbility);

	UPROPERTY(BlueprintAssignable)
	FMouseTargetDataDelegate ValidData;
	
	virtual void Activate() override;

private:

	void Test();

	UFUNCTION()
	void TestFunction();

	
	void SendMouseCursorData();

	UFUNCTION()
	void OnTargetDataReplicationCallback(const FGameplayAbilityTargetDataHandle& DataHandle, FGameplayTag ActivationTag);
	
};
