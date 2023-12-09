

#pragma once

#include "CoreMinimal.h"
#include "AuraBaseCharacter.h"
#include "AuraCharacter.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API AAuraCharacter : public AAuraBaseCharacter
{
	GENERATED_BODY()

public:

	AAuraCharacter();
	
protected:

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	class UCameraComponent* CameraComponent;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	class USpringArmComponent* SpringArmComponent;	
	
};
