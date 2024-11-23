

#pragma once

#include "CoreMinimal.h"
#include "AuraDamageGameplayAbility.h"
#include "AuraProjectileSpellAbility.generated.h"


class AAuraProjectile;

UCLASS()
class AURA_API UAuraProjectileSpellAbility : public UAuraDamageGameplayAbility
{
	GENERATED_BODY()

protected:

	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	TSubclassOf<AAuraProjectile> ProjectileClass;

	UFUNCTION(BlueprintCallable)
	void SpawnProjectile(const  FVector& ProjectileTargetLocation);
	
	UFUNCTION()
	void ValidatDataGet(const FGameplayAbilityTargetDataHandle& DataHandle);

	UFUNCTION()
	void EventReceived(FGameplayEventData GameplayEventData);

	UFUNCTION()
	void MontageCompleted();

	UFUNCTION(BlueprintImplementableEvent)
	void BP_EndAbilty();
	
	FVector Location;

	UPROPERTY(EditDefaultsOnly)
	UAnimMontage* ProjectileMontage;
};
