

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "GameplayEffectTypes.h"
#include "GameFramework/Actor.h"
#include "AuraEffectActor.generated.h"


UENUM(BlueprintType)
enum class EEffectApplicationPolicy : uint8
{
	OnOverlap, OnEndOverlap, DoNotApply
};

UENUM(BlueprintType)
enum class EEffectRemovalPolicy : uint8
{
	OnEndOverlap, DoNotApply
};


UCLASS()
class AURA_API AAuraEffectActor : public AActor
{
	GENERATED_BODY()
	
public:	

	AAuraEffectActor();
	virtual void PostInitializeComponents() override;

protected:
	
	UFUNCTION()
	virtual void SphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void SphereEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int OtherBodyIndex);
	
	UFUNCTION(BlueprintCallable)
	void ApplyEffectToTarget(AActor* Target,TSubclassOf<class UGameplayEffect> EffectToApply);

	UFUNCTION(BlueprintCallable)
	void RemoveEffectFromTarget(AActor* Target);
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TObjectPtr<class USphereComponent> Sphere;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TObjectPtr<class UStaticMeshComponent> Mesh;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TSubclassOf< UGameplayEffect> GameplayEffectClass;

	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	EEffectApplicationPolicy EffectApplicationPolicy = EEffectApplicationPolicy::OnOverlap;

	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	EEffectRemovalPolicy EffectRemovalPolicy = EEffectRemovalPolicy::DoNotApply;

	UPROPERTY()
	TMap<FActiveGameplayEffectHandle,UAbilitySystemComponent*> ActiveEffectHandlesMap;

	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	bool bShouldDestroyAfterApplyingEffect = true;

	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	bool bShouldDestroyAfterRemovingEffect = false;

	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	float EffectLevel = 1.f;
};