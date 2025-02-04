// Copyright Druid Mechanics


#include "UI/ViewModel/MVVM_LoadSlot.h"

void UMVVM_LoadSlot::InitializeSlot()
{
	// TODO: Check slot status based on loaded data
	SetWidgetSwitcherIndex.Broadcast(2);
}

void UMVVM_LoadSlot::SetPlayerName(const FString& InPlayerName)
{
	UE_MVVM_SET_PROPERTY_VALUE(PlayerName, InPlayerName);
}

void UMVVM_LoadSlot::SetLoadSlotName(const FString& InLoadSlotName)
{
	UE_MVVM_SET_PROPERTY_VALUE(LoadSlotName, InLoadSlotName);

}

void UMVVM_LoadSlot::SetSlotIndex(const FString& InSlotIndex)
{
	UE_MVVM_SET_PROPERTY_VALUE(SlotIndex, InSlotIndex);

}
