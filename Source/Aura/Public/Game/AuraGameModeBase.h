// Copyright Druid Mechanics

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "AuraGameModeBase.generated.h"

class UCharacterClassInfo;
/**
 * 
 */
UCLASS()
class AURA_API AAuraGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	
	UPROPERTY(EditDefaultsOnly, Category = "Character Class Defaults")
	TObjectPtr<UCharacterClassInfo> CharacterClassInfo;

	UPROPERTY(EditDefaultsOnly, Category = "Ability Info")
	class UAbilityInfo* AbilityInfo;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class USaveGame> LoadScreenSaveGameClass;
	
	void SaveSlotData(class UMVVM_LoadSlot* LoadSlot, int32 SlotIndex); 
};
