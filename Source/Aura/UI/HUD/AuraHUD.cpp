// Copyright Druid Mechanics


#include "AuraHUD.h"

#include "Aura/UI/WidgetControllers/AttributeMeunWidgetController.h"
#include "Aura/UI/WidgetControllers/AuraWidgetController.h"
#include "Aura/UI/WidgetControllers/OverlayWidgetController.h"
#include "Aura/UI/Widgets/AuraUserWidget.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/KismetSystemLibrary.h"

UOverlayWidgetController* AAuraHUD::GetOverlayWidgetController(const FWidgetControllerParams& WCParams)
{
	if (OverlayWidgetController ) return OverlayWidgetController;
	
	OverlayWidgetController = NewObject<UOverlayWidgetController>(this, OverlayWidgetControllerClass);
	OverlayWidgetController->SetWidgetControllerParams(WCParams);
	OverlayWidgetController->BindCallbacksToDependencies();
	return OverlayWidgetController;
}

void AAuraHUD::InitOverlay(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* ASC, UAttributeSet* AS)
{
	checkf(OverlayWidgetClass, TEXT("Overlay Widget Class uninitialized, please fill out BP_AuraHUD"));
	checkf(OverlayWidgetControllerClass, TEXT("Overlay Widget Controller Class uninitialized, please fill out BP_AuraHUD"));
	
	const FWidgetControllerParams WidgetControllerParams(PC, PS, ASC, AS);
	UOverlayWidgetController* WidgetController = GetOverlayWidgetController(WidgetControllerParams);

	UUserWidget* Widget = CreateWidget<UUserWidget>(GetWorld(), OverlayWidgetClass);
	OverlayWidget = Cast<UAuraUserWidget>(Widget);
	OverlayWidget->SetWidgetController(WidgetController);
	OverlayWidget->AddToViewport();
	WidgetController->BroadcastInitialValues();
}

UAttributeMeunWidgetController* AAuraHUD::GetAttributeMenuWidgetController(const FWidgetControllerParams& Params)
{
	if(AttributeMenuWidgetController ) return AttributeMenuWidgetController;
	
	AttributeMenuWidgetController = NewObject<UAttributeMeunWidgetController>(this,AttributeMenuWidgetControllerClass);
	AttributeMenuWidgetController->SetWidgetControllerParams(Params);
	AttributeMenuWidgetController->BindCallbacksToDependencies();
	return AttributeMenuWidgetController;
	
}
