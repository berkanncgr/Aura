

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "AuraWidgetController.generated.h"


class UAttributeSet;
class UAbilitySystemComponent;

USTRUCT(BlueprintType)
struct FWidgetControllerParams
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TObjectPtr<APlayerController> PlayerController = nullptr;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TObjectPtr<APlayerState> PlayerState = nullptr;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent = nullptr;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TObjectPtr<UAttributeSet> AttributeSet = nullptr;

	FWidgetControllerParams(){};

	FWidgetControllerParams(APlayerController* PC, APlayerState* PS,UAbilitySystemComponent* ASC,UAttributeSet* AS)
	{
		PlayerController = PC;
		PlayerState = PS;
		AbilitySystemComponent = ASC;
		AttributeSet = AS;
	}
};

UCLASS()
class AURA_API UAuraWidgetController : public UObject
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable)
	void SetWidgetControllerParams(const FWidgetControllerParams& Params)
	{
		PlayerController = Params.PlayerController;
		PlayerState = Params.PlayerState;
		AbilitySystemComponent = Params.AbilitySystemComponent;
		AttributeSet = Params.AttributeSet;
	}

protected:

	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<class APlayerController> PlayerController;

	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<class APlayerState> PlayerState;

	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<class UAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<class UAttributeSet> AttributeSet;
	
};
