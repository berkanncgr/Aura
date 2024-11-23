

#pragma once

#include "CoreMinimal.h"
#include "AuraCharacterBase.h"
#include "GameplayTagContainer.h"
#include "AuraCharacter.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API AAuraCharacter : public AAuraCharacterBase
{
	GENERATED_BODY()

public:

	AAuraCharacter();

	virtual void PossessedBy(AController* NewController) override;
	virtual void InitAbilityActorInfo() override;
	virtual void OnRep_PlayerState() override;
	virtual int32 GetPlayerLevel() override;

	UFUNCTION(BlueprintCallable)
	void SetFacingTarget(FVector FacingTarget);

	

protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	class UMotionWarpingComponent* MotionWarping;

	FORCEINLINE virtual void UpdateFacingTarget_Implementation(const FVector& Location) override
	{ SetFacingTarget (Location); }
	
};
