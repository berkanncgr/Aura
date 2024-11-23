


#include "Aura/Actors/AuraProjectile.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "Aura/Aura.h"
#include "Components/AudioComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"

AAuraProjectile::AAuraProjectile()
{
	PrimaryActorTick.bCanEverTick = false;
	bReplicates = true;

	Sphere = CreateDefaultSubobject<USphereComponent>("Sphere");
	Sphere->SetCollisionObjectType(ECC_Projectile);
	Sphere->SetCollisionEnabled(ECollisionEnabled::Type::QueryOnly);
	Sphere->SetCollisionResponseToChannels(ECR_Ignore);
	Sphere->SetCollisionResponseToChannel(ECC_WorldStatic,ECR_Overlap);
	Sphere->SetCollisionResponseToChannel(ECC_WorldDynamic,ECR_Overlap);
	Sphere->SetCollisionResponseToChannel(ECC_Pawn,ECR_Overlap);

	SetRootComponent(Sphere);

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>("ProjectileMovement");
	ProjectileMovement->InitialSpeed = 550;
	ProjectileMovement->MaxSpeed = 550;
	ProjectileMovement->ProjectileGravityScale = 0;

}


void AAuraProjectile::BeginPlay()
{
	Super::BeginPlay();
	SetLifeSpan(15);
	
	Sphere->OnComponentBeginOverlap.AddUniqueDynamic(this,&ThisClass::SphereBeginOverlap);
	LoopingSoundComponent =  UGameplayStatics::SpawnSoundAttached(LoopingSound,Sphere);

}

void AAuraProjectile::Destroyed()
{
	if(!bHit && HasAuthority())
	{
		UGameplayStatics::PlaySoundAtLocation(this,ImpactSound,GetActorLocation(),FRotator::ZeroRotator);
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(this,ImpactEffect,GetActorLocation());
		if(LoopingSoundComponent) LoopingSoundComponent->Stop();
	}
	
	Super::Destroyed();
}

void AAuraProjectile::SphereBeginOverlap(UPrimitiveComponent* PrimitiveComponent, AActor* OtherActor, UPrimitiveComponent* PrimitiveComponent1, int OtherBodyIndex, bool bArg, const FHitResult& HitResult)
{
	//if(!DamageEffectSpecHandle.Data.IsValid()) return;
	//if(DamageEffectSpecHandle.Data.Get()->GetContext().GetEffectCauser() == OtherActor) return;
	
	UGameplayStatics::PlaySoundAtLocation(this,ImpactSound,GetActorLocation(),FRotator::ZeroRotator);
	UNiagaraFunctionLibrary::SpawnSystemAtLocation(this,ImpactEffect,GetActorLocation());
	if(LoopingSoundComponent) LoopingSoundComponent->Stop();

	if(HasAuthority())
	{
		UAbilitySystemComponent* ASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(OtherActor);
		if(!ASC) return;

		ASC->ApplyGameplayEffectSpecToSelf(*DamageEffectSpecHandle.Data.Get());
		Destroy();
	}

	else bHit = true;
}


