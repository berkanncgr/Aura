


#include "AuraBaseCharacter.h"


AAuraBaseCharacter::AAuraBaseCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = false;
	PrimaryActorTick.bAllowTickOnDedicatedServer=false;

	Weapon = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Weapon"));
	Weapon->SetupAttachment(GetMesh(),"WeaponHandSocket");
	Weapon->SetCollisionEnabled(ECollisionEnabled::NoCollision);

}

AActor* AAuraBaseCharacter::GetSelfAsActor()
{
	return this;
}


void AAuraBaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}
