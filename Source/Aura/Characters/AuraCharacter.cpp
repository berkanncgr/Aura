

#include "AuraCharacter.h"

#include "AbilitySystemComponent.h"
#include "../../../../../../../../Programs/UE_5.3/Engine/Plugins/Animation/MotionWarping/Source/MotionWarping/Public/MotionWarpingComponent.h"
#include "Aura/AbilitySystem/AuraAbilitySystemComponent.h"
#include "Aura/Player/AuraPlayerController.h"
#include "Aura/Player/AuraPlayerState.h"
#include "Aura/UI/HUD/AuraHUD.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetSystemLibrary.h"


AAuraCharacter::AAuraCharacter()
{
	bUseControllerRotationPitch = bUseControllerRotationRoll = bUseControllerRotationYaw = false;
	
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 400.f, 0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	GetCapsuleComponent()->SetGenerateOverlapEvents(false);

	MotionWarping = CreateDefaultSubobject<UMotionWarpingComponent>("MotionWarping");
}

void AAuraCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	// Init Ability Actor Info for SERVER:
	InitAbilityActorInfo();
	AddCharacterAbilities();
}

void AAuraCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

	// Init Ability Actor Info for CLIENT:
	InitAbilityActorInfo();
}

int32 AAuraCharacter::GetPlayerLevel()
{
	AAuraPlayerState* PS = GetPlayerState<AAuraPlayerState>();
	return PS->GetPlayerLevel();
}



void AAuraCharacter::InitAbilityActorInfo()
{
	AAuraPlayerState* PS = GetPlayerState<AAuraPlayerState>();
	check(PS);
	PS->GetAbilitySystemComponent()->InitAbilityActorInfo(PS,this);
	AbilitySystemComponent = PS->GetAbilitySystemComponent();
	UAuraAbilitySystemComponent* AAS = Cast<UAuraAbilitySystemComponent>(AbilitySystemComponent);
	if(AAS) AAS->AbilityActorInfoSet();
	else { UKismetSystemLibrary::PrintString(GetWorld(),TEXT("Ability Cast NULL"));}
	AttributeSet = PS->GetAttributeSet();
	InitializeDefaultAttributes();



	AAuraPlayerController* Pc = Cast<AAuraPlayerController>(GetController());
	if(!Pc) return; // We Call InitAbilityActorInfo in OnRep. This cast is always null on OTHER CLIENTS !!!! Only valid if Character is Locally Controlled.

	AAuraHUD* Hud = Cast<AAuraHUD>(Pc->GetHUD());
	if(!Hud) return;
	Hud->InitOverlay(Pc,PS,AbilitySystemComponent,AttributeSet);
}

void AAuraCharacter::SetFacingTarget(FVector FacingTarget)
{
	FMotionWarpingTarget MotionWarpingTarget;
	MotionWarpingTarget.Location = FacingTarget;
	MotionWarpingTarget.Name = "FacingTarget";
	
	MotionWarping->AddOrUpdateWarpTarget(MotionWarpingTarget);
}

