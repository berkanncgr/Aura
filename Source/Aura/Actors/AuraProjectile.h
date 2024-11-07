#pragma once

#include "CoreMinimal.h"
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

protected:


	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	class USphereComponent* Sphere;

	UFUNCTION()
	virtual void SphereBeginOverlap(UPrimitiveComponent* PrimitiveComponent,AActor* OtherActor, UPrimitiveComponent* PrimitiveComponent1, int OtherBodyIndex, bool bArg, const FHitResult& HitResult);

	UFUNCTION()
	virtual void SphereEndOverlap(UPrimitiveComponent* PrimitiveComponent, AActor* OtherActor, UPrimitiveComponent* PrimitiveComponent1, int OtherBodyIndex);


};
