


#include "AuraGameplayTags.h"
#include "GameplayTagsManager.h"

FAuraGameplayTags FAuraGameplayTags::GameplayTags;

void FAuraGameplayTags::InitialieNativeGameplayTags()
{
	/* Primary Attributes */
	GameplayTags.Attributes_Primary_Strength	 = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Primary.Strength"),("Increases physical damage"));
	GameplayTags.Attributes_Primary_Intelligence = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Primary.Intelligence"),("Increases magical damage"));
	GameplayTags.Attributes_Primary_Resilience	 = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Primary.Resilience"),("Increases Armor and Armor Penetration"));
	GameplayTags.Attributes_Primary_Vigor		 = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Primary.Vigor"),("Increases Health"));

	/* Secondary Attributes */
	GameplayTags.Attributes_Secondary_Armor					= UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.Armor"),("Reduces damage taken, improves Block Chance"));
	GameplayTags.Attributes_Secondary_ArmorPenetration		= UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.ArmorPenetration"),("Ignores Percentage of enemy Armor, increases Critical Hit Chance"));
	GameplayTags.Attributes_Secondary_BlockChance			= UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.BlockChance"),("Chance to cut incoming damage in half"));
	GameplayTags.Attributes_Secondary_CriticalHitChance		= UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.CriticalHitChance"),("Chance to double damage plus critical hit bonus"));
	GameplayTags.Attributes_Secondary_CriticalHitDamage		= UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.CriticalHitDamage"),("Bonus damage added when a critical hit is scored"));
	GameplayTags.Attributes_Secondary_CriticalHitResistance = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.CriticalHitResistance"),("Reduces Critical Hit Chance of attacking enemies"));
	GameplayTags.Attributes_Secondary_HealthRegeneration	= UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.HealthRegeneration"),("Amount of Health regenerated every 1 second"));
	GameplayTags.Attributes_Secondary_ManaRegeneration		= UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.ManaRegeneration"),("Amount of Mana regenerated every 1 second"));
	GameplayTags.Attributes_Secondary_MaxHealth				= UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.MaxHealth"),("Maximum amount of Health obtainable"));
	GameplayTags.Attributes_Secondary_MaxMana				= UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.MaxMana"),("Maximum amount of Mana obtainable"));

	// Input Tags:
	GameplayTags.InputTag_LMB =	 UGameplayTagsManager::Get().AddNativeGameplayTag(FName("InputTag.LMB"),("Left Mouse Button Input"));
	GameplayTags.InputTag_RMB =	 UGameplayTagsManager::Get().AddNativeGameplayTag(FName("InputTag.RMB"),("Right Mouse Button Input"));
	GameplayTags.InputTag_1   =	 UGameplayTagsManager::Get().AddNativeGameplayTag(FName("InputTag.1"),("1 Key Input"));
	GameplayTags.InputTag_2   =	 UGameplayTagsManager::Get().AddNativeGameplayTag(FName("InputTag.2"),("2 Key Input"));
	GameplayTags.InputTag_3   =	 UGameplayTagsManager::Get().AddNativeGameplayTag(FName("InputTag.3"),("3 Key Input"));
	GameplayTags.InputTag_4   =	 UGameplayTagsManager::Get().AddNativeGameplayTag(FName("InputTag.4"),("4 Key Input"));
	GameplayTags.InputTag_Shift   =	 UGameplayTagsManager::Get().AddNativeGameplayTag(FName("InputTag.Shift"),("Shift Keys Input"));
	
	// Events:
	GameplayTags.Event_Montage_FireBolt = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Event.Montage.FireBolt"),("AM_Cast_FireBolt Montage Anim Notify"));

	GameplayTags.Damage = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Damage"),("Damage"));

	GameplayTags.Effects_HitReact = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Effects.HitReact"),("When damage is taken"));
}
