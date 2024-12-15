// Copyright Druid Mechanics

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/DataAsset.h"
#include "AbilityInfo_DataAsset.generated.h"


USTRUCT(BlueprintType)
struct FAuraAbilityInfo
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FGameplayTag AbilityTag;
	
	UPROPERTY(BlueprintReadOnly)
	FGameplayTag InputTag;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UTexture2D* Icon;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UMaterialInterface* BackgroundMaterial;
};

UCLASS()
class AURA_API UAbilityInfo_DataAsset : public UDataAsset
{
	GENERATED_BODY()

	public:
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray<FAuraAbilityInfo> AbilityInformation;

	FAuraAbilityInfo FinAbilityInfoForTag(const FGameplayTag AbilityTag, bool bWarnIfNotFound=false);
};
