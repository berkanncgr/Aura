

#pragma once

#include "CoreMinimal.h"
#include "Aura/UI/WidgetControllers/AuraWidgetController.h"
#include "AttributeMeunWidgetController.generated.h"

struct FGameplayAttribute;
struct FGameplayTag;
struct FAuraAttributeInfo;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FAttributeInfoSignature, const FAuraAttributeInfo&, Info);

UCLASS(Blueprintable,Blueprintable)
class AURA_API UAttributeMeunWidgetController : public UAuraWidgetController
{
	GENERATED_BODY()


public:

	virtual void BindCallbacksToDependencies() override;

	UFUNCTION(BlueprintCallable)
	virtual void BroadcastInitialValues() override;

	UPROPERTY(BlueprintAssignable)
	FAttributeInfoSignature AttributeInfoSignature;

protected:

	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	class UAttributeInfoDataAsset* AttributeInfoDataAsset;

	void BroadcastAttributeInfo(const FGameplayTag& AttributeTag, const FGameplayAttribute& Attribute) const;
};
