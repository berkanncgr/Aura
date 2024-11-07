


#include "Aura/AbilitySystem/Abilities/AuraProjectileSpellAbility.h"

#include "Aura/Actors/AuraProjectile.h"
#include "Aura/Interfaces/CombatInterface.h"


void UAuraProjectileSpellAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{

	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	return;
	const bool bIsServer  =  HasAuthority(&ActivationInfo);
	if(!bIsServer) return;

	ICombatInterface* CombatInterface = Cast<ICombatInterface>(GetAvatarActorFromActorInfo());
	if(!CombatInterface) return;
	const FVector SocketLocation = CombatInterface->GetCombatSocketLocation();
	
	FTransform SpawnTransform;
	SpawnTransform.SetLocation(SocketLocation);
	APawn* Pawn = Cast<APawn>(GetOwningActorFromActorInfo());

	AAuraProjectile* Projectile =  GetWorld()->SpawnActorDeferred<AAuraProjectile>(ProjectileClass,SpawnTransform,Pawn,Pawn,ESpawnActorCollisionHandlingMethod::AlwaysSpawn);
	
	//@tood: Give the projectile GameplayEffect Spec for causing damage.
	
	Projectile->FinishSpawning(SpawnTransform);
}

void UAuraProjectileSpellAbility::SpawnProjectile()
{
	if(! GetAvatarActorFromActorInfo()->HasAuthority()) return;

	ICombatInterface* CombatInterface = Cast<ICombatInterface>(GetAvatarActorFromActorInfo());
	if(!CombatInterface) return;
	const FVector SocketLocation = CombatInterface->GetCombatSocketLocation();
	
	FTransform SpawnTransform;
	SpawnTransform.SetLocation(SocketLocation);
	APawn* Pawn = Cast<APawn>(GetOwningActorFromActorInfo());

	AAuraProjectile* Projectile =  GetWorld()->SpawnActorDeferred<AAuraProjectile>(ProjectileClass,SpawnTransform,Pawn,Pawn,ESpawnActorCollisionHandlingMethod::AlwaysSpawn);
	
	//@tood: Give the projectile GameplayEffect Spec for causing damage.
	
	Projectile->FinishSpawning(SpawnTransform);

	//EndAbility();
}
