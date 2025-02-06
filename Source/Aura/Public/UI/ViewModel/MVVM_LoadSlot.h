// Copyright Druid Mechanics

#pragma once

#include "CoreMinimal.h"
#include "MVVMViewModelBase.h"
#include "Game/LoadScreenSaveGame.h"
#include "MVVM_LoadSlot.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FSetWidgetSwitcherIndex, int32, WidgetSwitcherIndex);

UCLASS()
class AURA_API UMVVM_LoadSlot : public UMVVMViewModelBase
{
	GENERATED_BODY()

public:
	
	void InitializeSlot();

	UPROPERTY(BlueprintAssignable)
	FSetWidgetSwitcherIndex SetWidgetSwitcherIndex;

	FString GetSlotIndex() const {return SlotIndex;}
	FString GetLoadSlotName() const {return LoadSlotName;}
	FString GetPlayerName() const {return PlayerName;}
	ESaveSlotStatus GetSlotStatus() const {return SlotStatus;}
	
	UFUNCTION(BlueprintCallable)
	void SetPlayerName(const FString& InPlayerName);
	
	UFUNCTION(BlueprintCallable)
	void SetLoadSlotName(const FString& InLoadSlotName);
	
	UFUNCTION(BlueprintCallable)
	void SetSlotIndex(const FString& InSlotIndex);

	UFUNCTION(BlueprintCallable)
	void SetSlotStatus(const ESaveSlotStatus& InSlotStatus);
	

protected:
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,FieldNotify,Setter,Getter,meta=(AllowPrivateAccess=true))
	FString PlayerName;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,FieldNotify,Setter,Getter,meta=(AllowPrivateAccess=true))
	FString LoadSlotName;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,FieldNotify,Setter,Getter,meta=(AllowPrivateAccess=true))
	FString SlotIndex;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,FieldNotify,Setter,Getter,meta=(AllowPrivateAccess=true))
	TEnumAsByte<ESaveSlotStatus> SlotStatus;
	
};

