

#pragma once

#include "CoreMinimal.h"
#include "Aura/UI/WidgetControllers/AuraWidgetController.h"
#include "AttributeMeunWidgetController.generated.h"

/**
 * 
 */
UCLASS(Blueprintable,Blueprintable)
class AURA_API UAttributeMeunWidgetController : public UAuraWidgetController
{
	GENERATED_BODY()


public:

	virtual void BindCallbacksToDependencies() override;
	virtual void BroadcastInitialValues() override;
};
