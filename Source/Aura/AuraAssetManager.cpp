


#include "AuraAssetManager.h"

#include "AbilitySystemGlobals.h"
#include "AuraGameplayTags.h"

UAuraAssetManager& UAuraAssetManager::Get()
{
	check(GEngine)
	return *Cast<UAuraAssetManager>(GEngine->AssetManager);
}

void UAuraAssetManager::StartInitialLoading()
{
	Super::StartInitialLoading();

	FAuraGameplayTags::InitialieNativeGameplayTags();

	// If we want to use target data, THIS IS BRUTAL: (Client broadcast the delegate and Server gets it!)
	UAbilitySystemGlobals::Get().InitGlobalData();
	
}
