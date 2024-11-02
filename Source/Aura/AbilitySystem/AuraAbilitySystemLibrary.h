

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "AuraAbilitySystemLibrary.generated.h"

class UAttributeMeunWidgetController;
class UAuraUserWidget;
class UOverlayWidgetController;
/**
 * 
 */
UCLASS()
class AURA_API UAuraAbilitySystemLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

	public:

	UFUNCTION(BlueprintPure, meta = (DisplayName = "Get Overlay Widget Controller"))
	static UOverlayWidgetController* GetOverlayWidgetController(const UObject* WorldContextObject);

	UFUNCTION(BlueprintPure, meta = (DisplayName = "Get Attribute Menu Widget Controller"))
	static UAttributeMeunWidgetController* GetAttributeMenuWidgetController(const UObject* WorldContextObject);
	
};
