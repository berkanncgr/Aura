


#include "Aura/AbilitySystem/Abilities/AuraProjectileSpellAbility.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "Abilities/Tasks/AbilityTask_PlayMontageAndWait.h"
#include "Abilities/Tasks/AbilityTask_WaitGameplayEvent.h"
#include "Aura/AuraGameplayTags.h"
#include "Aura/AbilitySystem/AbilityTasks/TargetDataUnderMouse.h"
#include "Aura/Actors/AuraProjectile.h"
#include "Aura/Interfaces/CombatInterface.h"


void UAuraProjectileSpellAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	return;
	UTargetDataUnderMouse* Task = UTargetDataUnderMouse::CreateTargetDataUnderMouse(this);
	Task->ValidData.AddUniqueDynamic(this,&ThisClass::ValidatDataGet);
	Task->Activate();
}



void UAuraProjectileSpellAbility::ValidatDataGet(const FGameplayAbilityTargetDataHandle& DataHandle)
{
	FGameplayAbilityTargetData* Data = DataHandle.Data[0].Get();
	FHitResult HitResult = *Data->GetHitResult();
	Location = HitResult.Location;
	DrawDebugSphere(GetWorld(),Location,100,100,FColor::Red,false,5);

	const FGameplayTag EventTag = FAuraGameplayTags::Get().Event_Montage_FireBolt;
	UAbilityTask_WaitGameplayEvent* AbilityTask = UAbilityTask_WaitGameplayEvent::WaitGameplayEvent(this,EventTag,nullptr,true,true);
	AbilityTask->EventReceived.AddDynamic(this,&ThisClass::EventReceived);

	UAbilityTask_PlayMontageAndWait* MontageAndWait = UAbilityTask_PlayMontageAndWait::CreatePlayMontageAndWaitProxy(this,"",ProjectileMontage,1);
	MontageAndWait->OnCompleted.AddUniqueDynamic(this,&UAuraProjectileSpellAbility::MontageCompleted);
	MontageAndWait->Activate();
}

// Look for why this is not triggering:
void UAuraProjectileSpellAbility::EventReceived(FGameplayEventData GameplayEventData)
{
	SpawnProjectile(Location);
}

void UAuraProjectileSpellAbility::MontageCompleted()
{
	BP_EndAbilty();
}

void UAuraProjectileSpellAbility::SpawnProjectile(const FVector& ProjectileTargetLocation)
{
	if(! GetAvatarActorFromActorInfo()->HasAuthority()) return;
 
	ICombatInterface* CombatInterface = Cast<ICombatInterface>(GetAvatarActorFromActorInfo());
	if(!CombatInterface) return;

	const FVector SocketLocation = CombatInterface->GetCombatSocketLocation();
	FRotator Rotation = (ProjectileTargetLocation - SocketLocation).Rotation();
	Rotation.Pitch = 0;
	
	FTransform SpawnTransform;
	SpawnTransform.SetLocation(SocketLocation);
	SpawnTransform.SetRotation(Rotation.Quaternion());

	APawn* Pawn = Cast<APawn>(GetOwningActorFromActorInfo());
	AAuraProjectile* Projectile =  GetWorld()->SpawnActorDeferred<AAuraProjectile>(ProjectileClass,SpawnTransform,Pawn,Pawn,ESpawnActorCollisionHandlingMethod::AlwaysSpawn);

	const UAbilitySystemComponent* SourceASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetAvatarActorFromActorInfo());
	const FGameplayEffectSpecHandle SpecHandle = SourceASC->MakeOutgoingSpec(ProjectileDamageEffectClass, GetAbilityLevel(), SourceASC->MakeEffectContext());
	UAbilitySystemBlueprintLibrary::AssignTagSetByCallerMagnitude(SpecHandle,FAuraGameplayTags::Get().Damage,Damage.GetValueAtLevel(GetAbilityLevel()));
	Projectile->DamageEffectSpecHandle = SpecHandle;
	
	Projectile->FinishSpawning(SpawnTransform);
}
