


#include "BaseAnimInstance.h"

#include "Aura/Interfaces/CharacterInterface.h"
#include "GameFramework/MovementComponent.h"
#include "Kismet/KismetMathLibrary.h"

void UBaseAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	CharacterRef = Cast<ICharacterInterface>(TryGetPawnOwner());
	if(!CharacterRef) return;
	MovementComponentRef = reinterpret_cast<UMovementComponent*>(CharacterRef->GetMovementCompFomInterface());
}

void UBaseAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	if(!MovementComponentRef) return;

	Super::NativeUpdateAnimation(DeltaSeconds);
	Speed = MovementComponentRef->Velocity;
	GroundSpeed = UKismetMathLibrary::VSizeXY(Speed);
	bShouldMove = GroundSpeed > 0;
}
