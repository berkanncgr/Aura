

#include "AuraCharacter.h"

#include "AbilitySystemComponent.h"
#include "Aura/Player/AuraPlayerController.h"
#include "Aura/Player/AuraPlayerState.h"
#include "Aura/UI/HUD/AuraHUD.h"


AAuraCharacter::AAuraCharacter()
{
	bUseControllerRotationPitch = bUseControllerRotationRoll = bUseControllerRotationYaw = false;
}

void AAuraCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	// Init Ability Actor Info for SERVER:
	InitAbilityActorInfo();
}

void AAuraCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

	// Init Ability Actor Info for CLIENT:
	InitAbilityActorInfo();
}

void AAuraCharacter::InitAbilityActorInfo()
{
	AAuraPlayerState* PS = GetPlayerState<AAuraPlayerState>();
	check(PS);
	PS->GetAbilitySystemComponent()->InitAbilityActorInfo(PS,this);
	AbilitySystemComponent = PS->GetAbilitySystemComponent();
	AttributeSet = PS->GetAttributeSet();

	AAuraPlayerController* Pc = Cast<AAuraPlayerController>(GetController());
	if(!Pc) return; // We Call InitAbilityActorInfo in OnRep. This cast is always null on OTHER CLIENTS !!!! Only valid if Character is Locally Controlled.

	AAuraHUD* Hud = Cast<AAuraHUD>(Pc->GetHUD());
	if(!Hud) return;
	Hud->InitOverlay(Pc,PS,AbilitySystemComponent,AttributeSet);
}


