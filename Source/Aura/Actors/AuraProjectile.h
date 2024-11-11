#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectTypes.h"
#include "GameFramework/Actor.h"
#include "AuraProjectile.generated.h"

UCLASS()
class AURA_API AAuraProjectile : public AActor
{
	GENERATED_BODY()
	
public:	

	AAuraProjectile();

	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	class UProjectileMovementComponent* ProjectileMovement;
	
	UPROPERTY(BlueprintReadWrite,meta=(ExposeOnSpawn = true))
	FGameplayEffectSpecHandle DamageEffectSpecHandle;

protected:
	
	virtual void BeginPlay() override;
	virtual void Destroyed() override;

	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	class USphereComponent* Sphere;

	UFUNCTION()
	virtual void SphereBeginOverlap(UPrimitiveComponent* PrimitiveComponent,AActor* OtherActor, UPrimitiveComponent* PrimitiveComponent1, int OtherBodyIndex, bool bArg, const FHitResult& HitResult);
	
	UPROPERTY(EditAnywhere,meta=(AllowPrivateAccess=true),BlueprintReadOnly)
	class UNiagaraSystem* ImpactEffect;

	UPROPERTY(EditAnywhere,meta=(AllowPrivateAccess=true),BlueprintReadOnly)
	class USoundBase* ImpactSound;

	UPROPERTY(EditAnywhere,meta=(AllowPrivateAccess=true),BlueprintReadOnly)
	class USoundBase* LoopingSound;

	UPROPERTY()
	UAudioComponent* LoopingSoundComponent;

	bool bHit = false;


};
