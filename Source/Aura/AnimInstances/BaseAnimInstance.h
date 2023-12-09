

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "BaseAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API UBaseAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:

	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

protected:

	class ICharacterInterface* CharacterRef;

	UPROPERTY(BlueprintReadWrite)
	class UMovementComponent* MovementComponentRef;

	UPROPERTY(BlueprintReadWrite)
	FVector Speed;

	UPROPERTY(BlueprintReadWrite)
	float GroundSpeed;

	UPROPERTY(BlueprintReadWrite)
	bool bShouldMove;
};
