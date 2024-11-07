


#include "Aura/Actors/AuraProjectile.h"

#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

AAuraProjectile::AAuraProjectile()
{
	PrimaryActorTick.bCanEverTick = false;
	bReplicates = true;

	Sphere = CreateDefaultSubobject<USphereComponent>("Sphere");
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

	Sphere->OnComponentBeginOverlap.AddUniqueDynamic(this,&ThisClass::SphereBeginOverlap);
	Sphere->OnComponentEndOverlap.AddUniqueDynamic(this,&ThisClass::SphereEndOverlap);
}

void AAuraProjectile::SphereBeginOverlap(UPrimitiveComponent* PrimitiveComponent, AActor* OtherActor, UPrimitiveComponent* PrimitiveComponent1, int OtherBodyIndex, bool bArg, const FHitResult& HitResult)
{
	
}

void AAuraProjectile::SphereEndOverlap(UPrimitiveComponent* PrimitiveComponent, AActor* OtherActor, UPrimitiveComponent* PrimitiveComponent1, int OtherBodyIndex)
{
	
}

