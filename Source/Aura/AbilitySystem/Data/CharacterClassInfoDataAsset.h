#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "CharacterClassInfoDataAsset.generated.h"

class UGameplayEffect;

UENUM(BlueprintType)
enum class ECharacterClass: uint8
{
	Elementalist, Warrior, Ranger
};


USTRUCT(BlueprintType)
struct FCharacterClassDefaultInfo
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<UGameplayEffect> PrimaryAttributes;
	
};

UCLASS()
class AURA_API UCharacterClassInfoDataAsset : public UDataAsset
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TMap<ECharacterClass, FCharacterClassDefaultInfo> CharacterClassInformation;
	
	// Common class defaults
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<UGameplayEffect> SecondaryAttributes;

	// Common class defaults
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<UGameplayEffect> VitalAttributes;

	FORCEINLINE	FCharacterClassDefaultInfo GetClassDefaultInfo(const ECharacterClass& CharacterClass) const
	{ return CharacterClassInformation.FindChecked(CharacterClass); }
};
