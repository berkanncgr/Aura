// Copyright Druid Mechanics

#pragma once

#include "CoreMinimal.h"
#include "MVVMViewModelBase.h"
#include "Game/LoadScreenSaveGame.h"
#include "MVVM_LoadSlot.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FSetWidgetSwitcherIndex, int32, WidgetSwitcherIndex);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FEnableSelectSlotButton, bool, bEnable);

UCLASS()
class AURA_API UMVVM_LoadSlot : public UMVVMViewModelBase
{
	GENERATED_BODY()

public:
	
	void InitializeSlot();

	UPROPERTY(BlueprintAssignable)
	FSetWidgetSwitcherIndex SetWidgetSwitcherIndex;

	UPROPERTY(BlueprintAssignable)
	FEnableSelectSlotButton EnableSelectSlotButton;

	int32 GetSlotIndex() const {return SlotIndex;}
	FString GetLoadSlotName() const {return LoadSlotName;}
	FString GetPlayerName() const {return PlayerName;}
	ESaveSlotStatus GetSlotStatus() const {return SlotStatus;}
	FString GetMapName() const { return MapName; }
	FName GetPlayerStartTag() const { return PlayerStartTag; }
	
	UFUNCTION(BlueprintCallable)
	void SetPlayerName(const FString& InPlayerName);
	
	UFUNCTION(BlueprintCallable)
	void SetLoadSlotName(const FString& InLoadSlotName);
	
	UFUNCTION(BlueprintCallable)
	void SetSlotIndex(const int32& InSlotIndex);

	UFUNCTION(BlueprintCallable)
	void SetSlotStatus(const ESaveSlotStatus& InSlotStatus);

	UFUNCTION(BlueprintCallable)
	void SetMapName(const FString& InMapName);

	UFUNCTION(BlueprintCallable)
	void SetPlayerStartTag(const FName& InTagName);

protected:
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,FieldNotify,Setter,Getter,meta=(AllowPrivateAccess=true))
	FString PlayerName;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,FieldNotify,Setter,Getter,meta=(AllowPrivateAccess=true))
	FString LoadSlotName;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,FieldNotify,Setter,Getter,meta=(AllowPrivateAccess=true))
	int32 SlotIndex;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,FieldNotify,Setter,Getter,meta=(AllowPrivateAccess=true))
	TEnumAsByte<ESaveSlotStatus> SlotStatus;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, FieldNotify, Setter, Getter, meta = (AllowPrivateAccess="true"));
	FString MapName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, FieldNotify, Setter, Getter, meta = (AllowPrivateAccess="true"));
	FName PlayerStartTag;
	
};

