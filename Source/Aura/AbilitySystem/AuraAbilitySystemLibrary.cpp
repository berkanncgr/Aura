


#include "Aura/AbilitySystem/AuraAbilitySystemLibrary.h"

#include "Aura/Player/AuraPlayerState.h"
#include "Aura/UI/HUD/AuraHUD.h"
#include "Aura/UI/WidgetControllers/AuraWidgetController.h"
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
