


#include "Aura/AbilitySystem/AuraAbilitySystemLibrary.h"

#include "AbilitySystemComponent.h"
#include "Aura/AuraAbilityTypes.h"
#include "Aura/Game/AuraGameModeBase.h"
#include "Aura/Player/AuraPlayerState.h"
#include "Aura/UI/HUD/AuraHUD.h"
#include "Aura/UI/WidgetControllers/AuraWidgetController.h"
#include "Data/CharacterClassInfoDataAsset.h"
#include "Kismet/GameplayStatics.h"

UOverlayWidgetController* UAuraAbilitySystemLibrary::GetOverlayWidgetController(const UObject* WorldContextObject)
{
	APlayerController* PC = UGameplayStatics::GetPlayerController(WorldContextObject,0);
	if(!PC) return nullptr;

	AAuraHUD* Hud = Cast<AAuraHUD>(PC->GetHUD());
	if(!Hud) return nullptr;

	AAuraPlayerState* PS = PC->GetPlayerState<AAuraPlayerState>();
	if(!PS) return nullptr;
	
	UAbilitySystemComponent* ASC = PS->GetAbilitySystemComponent();
	UAttributeSet* AS = PS->GetAttributeSet();
	const FWidgetControllerParams Params(PC,PS,ASC,AS);
	return Hud->GetOverlayWidgetController(Params);
}

UAttributeMeunWidgetController* UAuraAbilitySystemLibrary::GetAttributeMenuWidgetController(const UObject* WorldContextObject)
{
	APlayerController* PC = UGameplayStatics::GetPlayerController(WorldContextObject,0);
	if(!PC) return nullptr;

	AAuraHUD* Hud = Cast<AAuraHUD>(PC->GetHUD());
	if(!Hud) return nullptr;

	AAuraPlayerState* PS = PC->GetPlayerState<AAuraPlayerState>();
	if(!PS) return nullptr;
	
	UAbilitySystemComponent* ASC = PS->GetAbilitySystemComponent();
	UAttributeSet* AS = PS->GetAttributeSet();
	const FWidgetControllerParams Params(PC,PS,ASC,AS);

	return Hud->GetAttributeMenuWidgetController(Params);
}

void UAuraAbilitySystemLibrary::InitializeDefaultAttributes(UObject* WorldContextObject,ECharacterClass CharacterClass, float Level, UAbilitySystemComponent* ASC)
{
	AAuraGameModeBase* GM = Cast<AAuraGameModeBase>(UGameplayStatics::GetGameMode(WorldContextObject));
	if(!GM) return;

	AActor* AvatarActor = ASC->GetAvatarActor();
	
	UCharacterClassInfoDataAsset* ClassInfo = GM->CharacterClassInfo;
	FCharacterClassDefaultInfo ClassDefaultInfo = ClassInfo->GetClassDefaultInfo(CharacterClass);

	FGameplayEffectContextHandle PrimaryContextHandle = ASC->MakeEffectContext();
	PrimaryContextHandle.AddSourceObject(AvatarActor);
	const FGameplayEffectSpecHandle PrimarySpecHandle = ASC->MakeOutgoingSpec(ClassDefaultInfo.PrimaryAttributes,Level,PrimaryContextHandle);
	ASC->ApplyGameplayEffectSpecToSelf(*PrimarySpecHandle.Data.Get());

	FGameplayEffectContextHandle SecondaryContextHandle = ASC->MakeEffectContext();
	SecondaryContextHandle.AddSourceObject(AvatarActor);
	const FGameplayEffectSpecHandle SecondarySpecHandle =  ASC->MakeOutgoingSpec(ClassInfo->SecondaryAttributes,Level,SecondaryContextHandle);
	ASC->ApplyGameplayEffectSpecToSelf(*SecondarySpecHandle.Data.Get());

	FGameplayEffectContextHandle VitalContextHandle = ASC->MakeEffectContext();
	VitalContextHandle.AddSourceObject(AvatarActor);
	const FGameplayEffectSpecHandle VitalSpecHandle =  ASC->MakeOutgoingSpec(ClassInfo->VitalAttributes,Level,VitalContextHandle);
	ASC->ApplyGameplayEffectSpecToSelf(*VitalSpecHandle.Data.Get());
}

void UAuraAbilitySystemLibrary::GiveStartupAbilities(UObject* WorldContextObject,UAbilitySystemComponent* ASC)
{
	AAuraGameModeBase* GM = Cast<AAuraGameModeBase>(UGameplayStatics::GetGameMode(WorldContextObject));
	if(!GM) return;
	
	UCharacterClassInfoDataAsset* ClassInfo = GM->CharacterClassInfo;

	for(auto AbilityClass : ClassInfo->CommonAbilities)
	{
		FGameplayAbilitySpec AbilitySpec = FGameplayAbilitySpec(AbilityClass,1);
		ASC->GiveAbility(AbilitySpec);
	}
}

UCharacterClassInfoDataAsset* UAuraAbilitySystemLibrary::GetCharacterClassInfoDataAsset(const UObject* WorldContextObject)
{
	AAuraGameModeBase* GM = Cast<AAuraGameModeBase>(UGameplayStatics::GetGameMode(WorldContextObject));
	if(!GM) return nullptr;

	return GM->CharacterClassInfo;
}

UCurveTable* UAuraAbilitySystemLibrary::GetDamageCoefficientsCurve(const UObject* WorldContextObject)
{
	AAuraGameModeBase* GM = Cast<AAuraGameModeBase>(UGameplayStatics::GetGameMode(WorldContextObject));
	if(!GM) return nullptr;

	return GM->CharacterClassInfo->DamageCalculationCoefficients;
}

bool UAuraAbilitySystemLibrary::IsBlockedHit(const FGameplayEffectContextHandle& EffectContextHandle)
{
	const FGameplayEffectContext* EffectContext = EffectContextHandle.Get();
	const FAuraGameplayEffectContext* AuraEffectContext = static_cast<const FAuraGameplayEffectContext*>(EffectContext);

	if(!AuraEffectContext) return false;
	return AuraEffectContext->GetIsBlockedHit();
}

bool UAuraAbilitySystemLibrary::IsCriticalHit(const FGameplayEffectContextHandle& EffectContextHandle)
{
	const FGameplayEffectContext* EffectContext = EffectContextHandle.Get();
	const FAuraGameplayEffectContext* AuraEffectContext = static_cast<const FAuraGameplayEffectContext*>(EffectContext);

	if(!AuraEffectContext) return false;
	return AuraEffectContext->GetIsCriticalHit();
}

void UAuraAbilitySystemLibrary::SetIsBlockedHit(FGameplayEffectContextHandle& EffectContextHandle, bool InIsBlockedHit)
{
	FGameplayEffectContext* EffectContext = EffectContextHandle.Get();
	FAuraGameplayEffectContext* AuraEffectContext = static_cast<FAuraGameplayEffectContext*>(EffectContext);
	AuraEffectContext->SetBlockedHit(InIsBlockedHit);
}

void UAuraAbilitySystemLibrary::SetIsCriticalHit(FGameplayEffectContextHandle& EffectContextHandle, bool InIsCriticalHit)
{
	FGameplayEffectContext* EffectContext = EffectContextHandle.Get();
	FAuraGameplayEffectContext* AuraEffectContext = static_cast<FAuraGameplayEffectContext*>(EffectContext);
	AuraEffectContext->SetCriticalHit(InIsCriticalHit);
}
