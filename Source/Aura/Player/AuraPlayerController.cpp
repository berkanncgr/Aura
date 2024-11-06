


#include "AuraPlayerController.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "EnhancedInputSubsystems.h"
#include "NavigationPath.h"
#include "NavigationSystem.h"
#include "Aura/AuraGameplayTags.h"
#include "Aura/AbilitySystem/AuraAbilitySystemComponent.h"
#include "Aura/Interfaces/EnemyInterface.h"
#include "Aura/Input/AuraInputComponent.h"
#include "Components/SplineComponent.h"
#include "Kismet/KismetSystemLibrary.h"

AAuraPlayerController::AAuraPlayerController()
{
	// There's a first time for everything.d (How on earth this possible Hollysh....)
	bReplicates = true;

	AutoRunSpline = CreateDefaultSubobject<USplineComponent>("AutoRunSpline");

	
}

void AAuraPlayerController::BeginPlay()
{
	Super::BeginPlay();

	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;
	if(!ControlledPawn) ControlledPawn = GetPawn();

	FInputModeGameAndUI InputMode;
	InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	InputMode.SetHideCursorDuringCapture(false);
	SetInputMode(InputMode);
	
	//if(HasAuthority()) return;
	//@todo: try if there is no authority!!!!
	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	if(!Subsystem) return; // This cast is always null on OTHER CLIENTS !!!! Only valid if Character is Locally Controlled.
	Subsystem->AddMappingContext(AuraContext,0);
}

void AAuraPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	if(!ControlledPawn) ControlledPawn = GetPawn();

	UAuraInputComponent* AuraInputComponent = Cast<UAuraInputComponent>(InputComponent);
	AuraInputComponent->BindAction(MoveAction,ETriggerEvent::Triggered,this,&AAuraPlayerController::Move);
	AuraInputComponent->BindAbilityActions(InputConfig,this,&ThisClass::AbilityInputTagPressed,&ThisClass::AbilityInputTagReleased,&ThisClass::AbilityInputTagHeld);
}

void AAuraPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);
	CursorTrace();
	
}

class UAuraAbilitySystemComponent* AAuraPlayerController::GetAuraAbilitySystemComponent()
{
	if(!AuraAbilitySystemComponent) AuraAbilitySystemComponent = Cast<UAuraAbilitySystemComponent>(UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetPawn()));
	return AuraAbilitySystemComponent;
}

void AAuraPlayerController::CursorTrace()
{
	FHitResult HitResult;
	GetHitResultUnderCursor(ECC_Visibility,false,HitResult);
	if(!HitResult.bBlockingHit) return;
	if(!HitResult.GetActor()) return;
	
	LastHoveredActor = CurrentHoveredActor;
	CurrentHoveredActor = Cast<IEnemyInterface>(HitResult.GetActor());

	// Unhover the last and hover the current:
	
	if(!CurrentHoveredActor)
	{
		if(!LastHoveredActor) return;
		LastHoveredActor->UnHiglightActor();
		return;
	}
	
	if(CurrentHoveredActor == LastHoveredActor) return;
	if(LastHoveredActor) LastHoveredActor->UnHiglightActor();
	if(CurrentHoveredActor) CurrentHoveredActor->HighlightActor();
}

void AAuraPlayerController::Move(const FInputActionValue& InputValue)
{
	const FVector2d Value = InputValue.Get<FVector2d>();
	const FRotator Rotation = GetControlRotation();
	const FRotator YawRotation(0,Rotation.Yaw,0);
	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDirection =  FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	if(!ControlledPawn) return;
	ControlledPawn->AddMovementInput(ForwardDirection,Value.Y);
	ControlledPawn->AddMovementInput(RightDirection,Value.X);
}

void AAuraPlayerController::AbilityInputTagPressed(FGameplayTag InputTag)
{
	if(!GetAuraAbilitySystemComponent()) return;
	
	if(InputTag.MatchesTagExact(FAuraGameplayTags::Get().InputTag_LMB))
	{
		bAutoRunning = false;
		bIsMouseCursorTargeting = CurrentHoveredActor ? true : false;
	}
	
}

void AAuraPlayerController::AbilityInputTagReleased(FGameplayTag InputTag)
{
	if(!GetAuraAbilitySystemComponent()) return;
	
	if (!InputTag.MatchesTagExact(FAuraGameplayTags::Get().InputTag_LMB))
	{
		GetAuraAbilitySystemComponent()->AbilityInputTagReleased(InputTag);
		return;
	}

	if(bIsMouseCursorTargeting)
	{
		GetAuraAbilitySystemComponent()->AbilityInputTagReleased(InputTag);
		return;
	}

	if(FollowTime <= ShortPressTreshold)
	{
		FollowTime = 0;
		bIsMouseCursorTargeting = false;
		
		UNavigationPath* NavPath = UNavigationSystemV1::FindPathToLocationSynchronously(this,GetPawn()->GetActorLocation(),CachedDestination);
		if(!NavPath) return;

		AutoRunSpline->ClearSplinePoints();
		for(const FVector& Point :  NavPath->PathPoints)
		{
			AutoRunSpline->AddSplinePoint(Point,ESplineCoordinateSpace::World);
			DrawDebugSphere(GetWorld(),Point,8,8,FColor::Purple,false,5);
		}

		bAutoRunning = true;
	}


	
}

void AAuraPlayerController::AbilityInputTagHeld(FGameplayTag InputTag)
{
	if(!GetAuraAbilitySystemComponent()) return;

	if (!InputTag.MatchesTagExact(FAuraGameplayTags::Get().InputTag_LMB))
	{
		GetAuraAbilitySystemComponent()->AbilityInputTagHeld(InputTag);
		return;
	}

	if (bIsMouseCursorTargeting)
	{
		GetAuraAbilitySystemComponent()->AbilityInputTagHeld(InputTag);
		return;
	}
	
	FollowTime += GetWorld()->GetDeltaSeconds();

	FHitResult Hit;
	if (!GetHitResultUnderCursor(ECC_Visibility, false, Hit)) return;
	CachedDestination = Hit.ImpactPoint;
	
	APawn* _Pawn = GetPawn();
	if (!_Pawn) return;
	const FVector WorldDirection = (CachedDestination - _Pawn->GetActorLocation()).GetSafeNormal();
	ControlledPawn->AddMovementInput(WorldDirection);
	
}	
