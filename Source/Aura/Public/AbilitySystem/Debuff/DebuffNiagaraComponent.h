// Copyright Druid Mechanics

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "NiagaraComponent.h"
#include "DebuffNiagaraComponent.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API UDebuffNiagaraComponent : public UNiagaraComponent
{
	GENERATED_BODY()

	UDebuffNiagaraComponent();

public:

	UPROPERTY(EditDefaultsOnly)
	FGameplayTag DebuffTag;

protected:

	virtual void BeginPlay() override;

	UFUNCTION()
	void DebuffTagChanged(FGameplayTag GameplayTag, int NewCount);
	
};
