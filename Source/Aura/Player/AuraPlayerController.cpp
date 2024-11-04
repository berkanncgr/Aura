


#include "AuraPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "Aura/Interfaces/EnemyInterface.h"
#include "Aura/Input/AuraInputComponent.h"
#include "Kismet/KismetSystemLibrary.h"

AAuraPlayerController::AAuraPlayerController()
{
	// There's a first time for everything.d (How on earth this possible Hollysh....)
	bReplicates = true;

	
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
	
}

void AAuraPlayerController::AbilityInputTagReleased(FGameplayTag InputTag)
{
	
}

void AAuraPlayerController::AbilityInputTagHeld(FGameplayTag InputTag)
{
	
}	
