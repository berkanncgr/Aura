


#include "AuraEffectActor.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystemInterface.h"
#include "Aura/AbilitySystem/AuraAttributeSet.h"
#include "Components/SphereComponent.h"

AAuraEffectActor::AAuraEffectActor()
{
	PrimaryActorTick.bCanEverTick = PrimaryActorTick.bAllowTickOnDedicatedServer = PrimaryActorTick.bStartWithTickEnabled = false;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	SetRootComponent(Mesh);
	
	Sphere = CreateDefaultSubobject<USphereComponent>("Sphere");
	Sphere->SetupAttachment(Mesh);
}

void AAuraEffectActor::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	Sphere->OnComponentBeginOverlap.AddDynamic(this,&ThisClass::SphereBeginOverlap);
	Sphere->OnComponentEndOverlap.AddDynamic(this,&ThisClass::SphereEndOverlap);

}

void AAuraEffectActor::BeginPlay()
{
	Super::BeginPlay();
	
}

void AAuraEffectActor::SphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	IAbilitySystemInterface* ASCInterface = Cast<IAbilitySystemInterface>(OtherActor);
	if(!ASCInterface) return;

	const UAttributeSet* AS = ASCInterface->GetAbilitySystemComponent()->GetAttributeSet(UAuraAttributeSet::StaticClass());
	if(!AS) return;
	
	const UAuraAttributeSet* AAS = Cast<UAuraAttributeSet>(AS);
	if(!AAS) return;
	
	UAuraAttributeSet* AuraAttributeSet = const_cast<UAuraAttributeSet*>(AAS);
	AuraAttributeSet->SetMana(AAS->GetMana() + 5);
	Destroy();
}

void AAuraEffectActor::SphereEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int OtherBodyIndex)
{
	IAbilitySystemInterface* ASCInterface = Cast<IAbilitySystemInterface>(OtherActor);
	if(!ASCInterface) return;
}
