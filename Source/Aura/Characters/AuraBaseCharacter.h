

#pragma once

#include "CoreMinimal.h"
#include "Aura/Interfaces/CharacterInterface.h"
#include "GameFramework/Character.h"
#include "AuraBaseCharacter.generated.h"

UCLASS(Abstract)
class AURA_API AAuraBaseCharacter : public ACharacter, public ICharacterInterface
{
	GENERATED_BODY()

public:

	AAuraBaseCharacter();

	virtual AActor* GetSelfAsActor() override;
	
	FORCEINLINE virtual UPawnMovementComponent* GetMovementCompFomInterface() override
	{ return GetMovementComponent();}

protected:
	
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere,Category=Combat)
	TObjectPtr<USkeletalMeshComponent> Weapon;

};
