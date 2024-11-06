

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "GameplayTagContainer.h"
#include "AuraPlayerController.generated.h"

class IEnemyInterface;
class UInputAction;
class UInputMappingContext;
struct FInputActionValue;
class IEnemyInterface;

UCLASS()
class AURA_API AAuraPlayerController : public APlayerController
{
	GENERATED_BODY()

public:

	AAuraPlayerController();
	
protected:

	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;
	virtual void PlayerTick(float DeltaTime) override;
	
	class UAuraAbilitySystemComponent* GetAuraAbilitySystemComponent();
	

private:

	void CursorTrace();

    UPROPERTY(EditAnywhere,Category=Input,meta=(AllowPrivateAccess=true))
	TObjectPtr< UInputMappingContext> AuraContext;

	UPROPERTY(EditAnywhere,Category=Input,meta=(AllowPrivateAccess=true))
	TObjectPtr<UInputAction> MoveAction;
	
	UFUNCTION()
	void Move(const FInputActionValue& InputValue);

	UPROPERTY()
	APawn* ControlledPawn = nullptr;

	IEnemyInterface* LastHoveredActor;
	IEnemyInterface* CurrentHoveredActor;

	UPROPERTY(EditDefaultsOnly,Category=Input,meta=(AllowPrivateAccess=true))
	class UAuraInputConfigDataAsset* InputConfig;

	void AbilityInputTagPressed(FGameplayTag InputTag);
	void AbilityInputTagReleased(FGameplayTag InputTag);
	void AbilityInputTagHeld(FGameplayTag InputTag);

	UPROPERTY(BlueprintReadWrite,meta=(AllowPrivateAccess=true))
	UAuraAbilitySystemComponent* AuraAbilitySystemComponent;

	FVector CachedDestination = FVector::ZeroVector;

	float FollowTime = 0.0f, ShortPressTreshold = 0.5f;

	// In cm.
	UPROPERTY(EditDefaultsOnly)
	float AutoRunAcceptanceRadius = 50.f;

	bool bAutoRunning = false;

	bool bIsMouseCursorTargeting = false;

	UPROPERTY(EditAnywhere)
	class USplineComponent* AutoRunSpline = nullptr;
};
