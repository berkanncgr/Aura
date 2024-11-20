


#include "Aura/AbilitySystem/AbilityTasks/TargetDataUnderMouse.h"

#include "AbilitySystemComponent.h"
#include "Kismet/KismetSystemLibrary.h"

UTargetDataUnderMouse* UTargetDataUnderMouse::CreateTargetDataUnderMouse(UGameplayAbility* OwningAbility)
{
	UTargetDataUnderMouse* Obj = NewAbilityTask<UTargetDataUnderMouse>(OwningAbility);
	return Obj;

	// What happens if we call Activate() here?
}


void UTargetDataUnderMouse::Activate()
{
	if(IsLocallyControlled())
	{
		//Send Target Data to Server.
		SendMouseCursorData();
	}
	
	else
	{
		// We are on server, listen for target data.
		const FGameplayAbilitySpecHandle SpecHandle = GetAbilitySpecHandle();
		const FPredictionKey PredictionKey = GetActivationPredictionKey();
		AbilitySystemComponent.Get()->AbilityTargetDataSetDelegate(SpecHandle,PredictionKey).AddUObject(this,&ThisClass::OnTargetDataReplicationCallback);
		const bool bCalledDelegate = AbilitySystemComponent.Get()->CallReplicatedTargetDataDelegatesIfSet(SpecHandle,PredictionKey);
		if(!bCalledDelegate) SetWaitingOnRemotePlayerData();
	}

	
}

void UTargetDataUnderMouse::Test()
{
	FTimerHandle TimerHandle;
	GetWorld()->GetTimerManager().SetTimer(TimerHandle,this,&ThisClass::TestFunction,0.016,true);
}

void UTargetDataUnderMouse::TestFunction()
{
	UKismetSystemLibrary::PrintString(GetWorld(),TEXT("Test Function"),1,1,FColor::Red,0.016);
}


void UTargetDataUnderMouse::SendMouseCursorData()
{
	// THIS IS MAGIC!!!!! (Research MORE!!)
	FScopedPredictionWindow ScopedPredictionWindow(AbilitySystemComponent.Get());
	 
	APlayerController* PC = Ability->GetCurrentActorInfo()->PlayerController.Get();
	if(!PC) return;

	FHitResult HitResult;
	PC->GetHitResultUnderCursor(ECC_Visibility, false, HitResult);
	//ValidData.Broadcast(HitResult.Location);
	
	FGameplayAbilityTargetData_SingleTargetHit* DataSenderToServer = new FGameplayAbilityTargetData_SingleTargetHit();
	DataSenderToServer->HitResult = HitResult;

	FGameplayAbilityTargetDataHandle DataHandle;
	DataHandle.Add(DataSenderToServer);
	
	AbilitySystemComponent->ServerSetReplicatedTargetData(GetAbilitySpecHandle(),GetActivationPredictionKey(),DataHandle,FGameplayTag(), AbilitySystemComponent->ScopedPredictionKey);

	if(ShouldBroadcastAbilityTaskDelegates())
	{
		ValidData.Broadcast(DataHandle);
	}
}

void UTargetDataUnderMouse::OnTargetDataReplicationCallback(const FGameplayAbilityTargetDataHandle& DataHandle, FGameplayTag ActivationTag)
{
	AbilitySystemComponent->ConsumeClientReplicatedTargetData(GetAbilitySpecHandle(),GetActivationPredictionKey());

	if(ShouldBroadcastAbilityTaskDelegates())
	{
		ValidData.Broadcast(DataHandle);
	}
}
