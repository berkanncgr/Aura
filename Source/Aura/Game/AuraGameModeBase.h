#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "AuraGameModeBase.generated.h"


UCLASS()
class AURA_API AAuraGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:

		

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	class UCharacterClassInfoDataAsset* CharacterClassInfo;
	
};
