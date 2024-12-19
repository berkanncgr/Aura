// Copyright Druid Mechanics

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "LevelUpInfo_DataAsset.generated.h"

USTRUCT()
struct FauraLevelUpInfo
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly)
	int32 LevelUpRequirement = 0;

	UPROPERTY(EditDefaultsOnly)
	int32 AttributePointReward = 0;

	UPROPERTY(EditDefaultsOnly)
	int32 SpellPointReward = 1;
	
};
UCLASS()
class AURA_API ULevelUpInfo_DataAsset : public UDataAsset
{
	GENERATED_BODY()

	public:

	UPROPERTY(EditDefaultsOnly)
	TArray<FauraLevelUpInfo> LevelUpInformation;

	int32 FindLevelForXP(int32 XP);
	
};
