


#include "AuraEnemy.h"

AAuraEnemy::AAuraEnemy()
{
	GetMesh()->SetCollisionResponseToChannel(ECC_Visibility,ECR_Block);
}

void AAuraEnemy::HighlightActor()
{
	GetMesh()->SetCustomDepthStencilValue(250);
	GetMesh()->SetRenderCustomDepth(true);
	Weapon->SetCustomDepthStencilValue(250);
	Weapon->SetRenderCustomDepth(true);
}

void AAuraEnemy::UnHiglightActor()
{
	GetMesh()->SetCustomDepthStencilValue(0);
	GetMesh()->SetRenderCustomDepth(false);
	Weapon->SetCustomDepthStencilValue(0);
	Weapon->SetRenderCustomDepth(false);
}
