#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/DataAsset.h"
#include "AttributeInfoDataAsset.generated.h"


USTRUCT(BlueprintType)
struct FAuraAttributeInfo
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	FGameplayTag AttributeTag;

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	FText AttributeName = FText();

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	FText AttributeDescribtion = FText();

	UPROPERTY(BlueprintReadOnly)
	float AttributeValue = 0.f;
};

/* // TEST PASSED !
USTRUCT(BlueprintType)
struct FTestStruct
{
	GENERATED_BODY()
	
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	FText AttributeName = FText();

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	FText AttributeDescribtion = FText();

	UPROPERTY(BlueprintReadOnly)
	float AttributeValue = 0.f;
};
*/

UCLASS()
class AURA_API UAttributeInfoDataAsset : public UDataAsset
{
	GENERATED_BODY()

public:

	FAuraAttributeInfo FindAttributeInfoForTag(const FGameplayTag& AttributeTag, bool bLogNotFound = false) const;
	
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	TArray<FAuraAttributeInfo> AttributeInformation;

	//UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	//TMap<FGameplayTag,FTestStruct > TestMap;
	
};
