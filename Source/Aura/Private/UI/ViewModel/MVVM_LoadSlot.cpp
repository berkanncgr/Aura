// Copyright Druid Mechanics


#include "UI/ViewModel/MVVM_LoadSlot.h"

void UMVVM_LoadSlot::InitializeSlot()
{
	const int32 WidgetSwitcherIndex = SlotStatus.GetValue();
	SetWidgetSwitcherIndex.Broadcast(WidgetSwitcherIndex);
}

void UMVVM_LoadSlot::SetPlayerName(const FString& InPlayerName)
{
	UE_MVVM_SET_PROPERTY_VALUE(PlayerName, InPlayerName);
}

void UMVVM_LoadSlot::SetLoadSlotName(const FString& InLoadSlotName)
{
	UE_MVVM_SET_PROPERTY_VALUE(LoadSlotName, InLoadSlotName);
}

void UMVVM_LoadSlot::SetSlotIndex(const int32& InSlotIndex)
{
	UE_MVVM_SET_PROPERTY_VALUE(SlotIndex, InSlotIndex);
}

void UMVVM_LoadSlot::SetSlotStatus(const ESaveSlotStatus& InSlotStatus)
{
	UE_MVVM_SET_PROPERTY_VALUE(SlotStatus, InSlotStatus);
}

void UMVVM_LoadSlot::SetMapName(const FString& InMapName)
{
	UE_MVVM_SET_PROPERTY_VALUE(MapName, InMapName);
}

void UMVVM_LoadSlot::SetPlayerStartTag(const FName& InTagName)
{
	UE_MVVM_SET_PROPERTY_VALUE(PlayerStartTag, InTagName);

}
