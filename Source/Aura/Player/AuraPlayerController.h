

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
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
};
