

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "CombatInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UCombatInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class AURA_API ICombatInterface
{
	GENERATED_BODY()

public:

	virtual int32 GetPlayerLevel() { return 0;}

	// Projectile spawn location:
	virtual FVector GetCombatSocketLocation() { return FVector::ZeroVector;}

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void UpdateFacingTarget(const FVector& Location);
	virtual void UpdateFacingTarget_Implementation(const FVector& Location){};
};
