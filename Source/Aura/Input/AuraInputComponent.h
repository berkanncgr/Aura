

#pragma once

#include "CoreMinimal.h"
#include "AuraInputConfigDataAsset.h"
#include "EnhancedInputComponent.h"
#include "AuraInputComponent.generated.h"

class UAuraInputConfigDataAsset;
/**
 * 
 */
UCLASS()
class AURA_API UAuraInputComponent : public UEnhancedInputComponent
{
	GENERATED_BODY()

public:

	template<class UserClass, typename PressedFuncType, typename ReleasedFuncType, typename HeldFuncType>
	void BindAbilityActions(const UAuraInputConfigDataAsset* InputConfig,UserClass* Object, PressedFuncType PressedFunc,ReleasedFuncType ReleasedFunc, HeldFuncType HeldFunc);
	
};

template <class UserClass, typename PressedFuncType, typename ReleasedFuncType, typename HeldFuncType>
void UAuraInputComponent::BindAbilityActions(const UAuraInputConfigDataAsset* InputConfig, UserClass* Object, PressedFuncType PressedFunc, ReleasedFuncType ReleasedFunc, HeldFuncType HeldFunc)
{
	if(!InputConfig) { UE_LOG(LogTemp,Error,TEXT("InputConfig is NULL")); return; }

	for(const FAuraInputAction& Action : InputConfig->AbilityInputActions)
	{
		if(!Action.InputAction) continue;
		if(!Action.InputTag.IsValid()) continue;

		if(PressedFunc)  BindAction(Action.InputAction,ETriggerEvent::Started,Object,PressedFunc,Action.InputTag);
		if(ReleasedFunc) BindAction(Action.InputAction,ETriggerEvent::Completed,Object,ReleasedFunc,Action.InputTag);
		if(HeldFunc)	 BindAction(Action.InputAction,ETriggerEvent::Triggered,Object,HeldFunc,Action.InputTag);
	}
}

