

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "GameplayTagContainer.h"
#include "AuraPlayerController.generated.h"

class UDamageTextWidgetComponent;
class UWidgetComponent;
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

	UFUNCTION(Client,Reliable)
	void Client_ShowDamageNumber(float DamageAmount, ACharacter* TargetCharacter);
	
protected:

	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;
	void AutoRun();
	virtual void PlayerTick(float DeltaTime) override;
	
	class UAuraAbilitySystemComponent* GetASC();

	FHitResult CursorHit;



private:
	
	void CursorTrace();

    UPROPERTY(EditAnywhere,Category=Input,meta=(AllowPrivateAccess=true))
	TObjectPtr< UInputMappingContext> AuraContext;

	UPROPERTY(EditAnywhere,Category=Input,meta=(AllowPrivateAccess=true))
	TObjectPtr<UInputAction> MoveAction;

	UPROPERTY(EditAnywhere,Category=Input,meta=(AllowPrivateAccess=true))
	UInputAction* ShiftAction;
	
	UFUNCTION()
	void Move(const FInputActionValue& InputValue);

	UFUNCTION()
	FORCEINLINE void ShiftActionStarted()
	{ bIsShiftKeyDown = true; }

	UFUNCTION()
	FORCEINLINE void ShiftActionCompleted()
	{ bIsShiftKeyDown = false; }

	bool bIsShiftKeyDown = false;
	
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

	float FollowTime = 0.0f, ShortPressThreshold = 0.5f;

	// In cm.
	UPROPERTY(EditDefaultsOnly)
	float AutoRunAcceptanceRadius = 50.f;

	bool bAutoRunning = false;

	bool bIsMouseCursorTargeting = false;

	UPROPERTY(EditAnywhere)
	class USplineComponent* Spline = nullptr;

	UPROPERTY(EditDefaultsOnly,meta=(AllowPrivateAccess=true),BlueprintReadOnly)
	TSubclassOf<UDamageTextWidgetComponent> DamageTextComponentClass;
};
