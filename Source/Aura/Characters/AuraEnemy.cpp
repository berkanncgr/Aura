


#include "AuraEnemy.h"

#include "AbilitySystemComponent.h"
#include "Aura/AuraGameplayTags.h"
#include "Aura/AbilitySystem/AuraAbilitySystemComponent.h"
#include "Aura/AbilitySystem/AuraAbilitySystemLibrary.h"
#include "Aura/AbilitySystem/AuraAttributeSet.h"
#include "Aura/UI/Widgets/AuraUserWidget.h"
#include "Components/WidgetComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetSystemLibrary.h"

AAuraEnemy::AAuraEnemy()
{
	GetMesh()->SetCollisionResponseToChannel(ECC_Visibility,ECR_Block);

	AbilitySystemComponent = CreateDefaultSubobject<UAuraAbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent ->SetIsReplicated(true);
	AbilitySystemComponent ->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);
	
	AttributeSet = CreateDefaultSubobject<UAuraAttributeSet>("AttributeSet");

	HealthBarWidgetComponent = CreateDefaultSubobject<UWidgetComponent>("HealthBarWidgetComponent");
	HealthBarWidgetComponent ->SetupAttachment(GetRootComponent());
}


void AAuraEnemy::BeginPlay()
{
	Super::BeginPlay();
	InitAbilityActorInfo();
	InitializeHealthBarWidget();

	AbilitySystemComponent->RegisterGameplayTagEvent(FAuraGameplayTags::Get().Effects_HitReact,EGameplayTagEventType::NewOrRemoved).AddUObject(this,&ThisClass::HitReactTagChanged);
}

void AAuraEnemy::HitReactTagChanged(const FGameplayTag CallbackTag, int32 NewCount)
{
	bHitReacting = NewCount > 0;
	GetCharacterMovement()->MaxWalkSpeed = bHitReacting ? 0 : BaseWalkSpeed;
}

void AAuraEnemy::InitAbilityActorInfo()
{
	AbilitySystemComponent->InitAbilityActorInfo(this,this);
	UAuraAbilitySystemComponent* AAS = Cast<UAuraAbilitySystemComponent>(AbilitySystemComponent);
	AAS->AbilityActorInfoSet();

	InitializeDefaultAttributes();
}

void AAuraEnemy::InitializeDefaultAttributes()
{
	UAuraAbilitySystemLibrary::InitializeDefaultAttributes(GetWorld(),CharacterClass,Level,AbilitySystemComponent);
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

void AAuraEnemy::InitializeHealthBarWidget()
{
	UAuraUserWidget* HealthBar = Cast<UAuraUserWidget>(HealthBarWidgetComponent->GetWidget());
	HealthBar->SetWidgetController(this);
	
	UAuraAttributeSet* AS = CastChecked<UAuraAttributeSet>(AttributeSet);
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AS->GetHealthAttribute()).AddLambda([this](const FOnAttributeChangeData& Data)
	{
		OnHealthChanged.Broadcast(Data.NewValue);
	});
	
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AS->GetMaxHealthAttribute()).AddLambda([this](const FOnAttributeChangeData& Data)
	{
		OnMaxHealthChanged.Broadcast(Data.NewValue);
	});
	
	OnHealthChanged.Broadcast(AS->GetHealth());
	OnMaxHealthChanged.Broadcast(AS->GetMaxHealth());
}