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
	class ULoadScreenSaveGame* GetSaveSlotData(const FString& SlotName, int32 SlotIndex) const;

	static void DeleteSlot(const FString& SlotName, int32 SlotIndex);

	void TravelToMap(UMVVM_LoadSlot* Slot);

	UPROPERTY(EditDefaultsOnly)
	FString DefaultMapName;
	
	UPROPERTY(EditDefaultsOnly)
	TSoftObjectPtr<UWorld> DefaultMap;
	
	UPROPERTY(EditDefaultsOnly)
	TMap<FString, TSoftObjectPtr<UWorld>> Maps;
	
	UPROPERTY(EditDefaultsOnly)
	FName DefaultPlayerStartTag;
	
protected:
	
	virtual void BeginPlay() override;
	
	virtual AActor* ChoosePlayerStart_Implementation(AController* Player) override;


};
