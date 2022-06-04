// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterBase.h"
#include "AbilitySystemComponent.h"
#include "AbilityStudyDemo/AbilityStudyDemo.h"
#include "AbilityStudyDemo/GAS/AttributeSetBase.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
ACharacterBase::ACharacterBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	IsDied = false;
	
	AbilitySystemComp = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilitySystemComp"));
	AttributeSet = CreateDefaultSubobject<UAttributeSetBase>(TEXT("AttributeSet"));
	
}

// Called when the game starts or when spawned
void ACharacterBase::BeginPlay()
{
	Super::BeginPlay();

	if(IsValid(AbilitySystemComp))
	{
		AbilitySystemComp->GetGameplayAttributeValueChangeDelegate(UAttributeSetBase::GetHealthAttribute()).AddUObject(this,&ACharacterBase::OnHealthAttributeChanged);
		AbilitySystemComp->GetGameplayAttributeValueChangeDelegate(UAttributeSetBase::GetMoveSpeedAttribute()).AddUObject(this,&ACharacterBase::OnMoveSpeedAttributeChanged);
	}
	
}

// Called every frame
void ACharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ACharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if(AbilitySystemComp)
	{
		AbilitySystemComp->BindAbilityActivationToInputComponent(PlayerInputComponent,
			FGameplayAbilityInputBinds(FString("Confirm"), FString("Cancel"),
				FString("EAbilityInputID"), static_cast<int32>(EAbilityInputID::Confirm),
				static_cast<int32>(EAbilityInputID::Cancel)));
		// AbilitySystemComp->BindAbilityActivationToInputComponent(PlayerInputComponent,
		// 	FGameplayAbilityInputBinds(FString("Confirm"),
		// 	FString("Cancel"),FString("EAbilityInputID"),
		// 	static_cast<int32>(EAbilityInputID::Confirm),static_cast<int32>(EAbilityInputID::Cancel)));
	}
}

UAbilitySystemComponent* ACharacterBase::GetAbilitySystemComponent() const
{
	return AbilitySystemComp;
}

void ACharacterBase::GetAbility(TSubclassOf<UGameplayAbility> Ability)
{
	if(AbilitySystemComp)
	{
		if (HasAuthority() && Ability)
			AbilitySystemComp->GiveAbility(FGameplayAbilitySpec(Ability));
		AbilitySystemComp->InitAbilityActorInfo(this, this);
	}

}

void ACharacterBase::GiveAbilityInput(TSubclassOf<UGamePlayAbilityBase> Ability)
{
	if(AbilitySystemComp && HasAuthority() && Ability)
	{
		AbilitySystemComp->GiveAbility(FGameplayAbilitySpec(Ability,1,
			static_cast<int32>(Ability.GetDefaultObject()->AbilityInputID),this));
	}

}

void ACharacterBase::OnHealthAttributeChanged(const FOnAttributeChangeData& Data)
{
	if(IsValid(AbilitySystemComp))
		HealthChangeEvent.Broadcast(Data.NewValue,AbilitySystemComp->GetNumericAttribute(UAttributeSetBase::GetMaxHealthAttribute()));
}

void ACharacterBase::OnMoveSpeedAttributeChanged(const FOnAttributeChangeData& Data)
{
	// if()
	UCharacterMovementComponent* MoveCom = Cast<UCharacterMovementComponent>(GetCharacterMovement());
	MoveCom->MaxWalkSpeed = Data.NewValue;
	UE_LOG(LogTemp,Warning,TEXT("Character::MaxWalkSpeed=%f"),MoveCom->MaxWalkSpeed);

}

void ACharacterBase::Died()
{
	IsDied = true;
	float fAnimDuration = PlayAnimMontage(DeathMontage);

	UE_LOG(LogTemp,Warning,TEXT("DeathAnimDuration=%f"),fAnimDuration);
	
	FTimerHandle TimerHandle;
	if(fAnimDuration>0.0f)
		GetWorldTimerManager().SetTimer(TimerHandle,this,&ACharacterBase::DestroyTimer,fAnimDuration,false);
	else
		Destroy();
}

void ACharacterBase::DestroyTimer()
{
	Destroy();
}


