


#include "AuraEnemy.h"
#include "Kismet/KismetSystemLibrary.h"

void AAuraEnemy::HighlightActor()
{
	UKismetSystemLibrary::PrintString(GetWorld(),FString::Printf(TEXT("H: %s"),*GetName()));
}

void AAuraEnemy::UnHiglightActor()
{
	UKismetSystemLibrary::PrintString(GetWorld(),FString::Printf(TEXT("UH: %s"),*GetName()));
}
