

#pragma once

#include "CoreMinimal.h"
#include "AuraBaseCharacter.h"
#include "Aura/Interfaces/EnemyInterface.h"
#include "AuraEnemy.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API AAuraEnemy : public AAuraBaseCharacter, public IEnemyInterface
{
	GENERATED_BODY()

public:

	AAuraEnemy();
	virtual void BeginPlay() override;
	
	virtual void HighlightActor() override;
	virtual void UnHiglightActor() override;

protected:

	virtual void InitAbilityActorInfo() override;
	
};
