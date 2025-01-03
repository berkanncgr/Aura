

#pragma once

#include "CoreMinimal.h"
#include "AuraCharacterBase.h"
#include "Aura/Interfaces/EnemyInterface.h"
#include "Aura/UI/WidgetControllers/OverlayWidgetController.h"
#include "Aura/AbilitySystem/Data/CharacterClassInfoDataAsset.h"
#include "AuraEnemy.generated.h"

UCLASS()
class AURA_API AAuraEnemy : public AAuraCharacterBase, public IEnemyInterface
{
	GENERATED_BODY()

public:

	AAuraEnemy();
	void InitializeHealthBarWidget();


	virtual void BeginPlay() override;
	
	virtual void HighlightActor() override;
	virtual void UnHiglightActor() override;

	FORCEINLINE virtual int32 GetPlayerLevel() override { return Level; }
	FORCEINLINE virtual ECharacterClass GetCharacterClass() const override { return CharacterClass; }

	void HitReactTagChanged(const FGameplayTag CallbackTag, int32 NewCount);
	virtual void Die_Implementation() override;
	
	
protected:

	virtual void InitAbilityActorInfo() override;
	virtual void InitializeDefaultAttributes() override;

	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	ECharacterClass CharacterClass = ECharacterClass::Ranger;
	
	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	int32 Level = 1;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    class UWidgetComponent* HealthBarWidgetComponent;

	UPROPERTY(BlueprintAssignable)
	FOnAttributeChangedSignature OnHealthChanged;

	UPROPERTY(BlueprintAssignable)
	FOnAttributeChangedSignature OnMaxHealthChanged;

	UPROPERTY(BlueprintReadOnly)
	bool bHitReacting = false;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float BaseWalkSpeed = 250;

};
