// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "Abilities/GameplayAbility.h"
#include "AttributeSet.h"
#include "AbilityStudyDemo/GAS/GamePlayAbilityBase.h"
#include "CharacterBase.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FoNHealthChangeEvent, float, Health, float, MaxHealth);

UCLASS()
class ABILITYSTUDYDEMO_API ACharacterBase : public ACharacter,public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACharacterBase();

public:

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Ability")
	class UAbilitySystemComponent* AbilitySystemComp;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Attribute")
		class UAttributeSetBase* AttributeSet;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
		bool IsDied;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
		class UAnimMontage* DeathMontage;
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const;

	UFUNCTION(BlueprintCallable, Category = "Ability")
		void GetAbility(TSubclassOf<UGameplayAbility> Ability);

	UFUNCTION(BlueprintCallable, Category = "Ability")
		void GiveAbilityInput(TSubclassOf<UGamePlayAbilityBase> Ability);

	UPROPERTY(BlueprintAssignable,Category="Ability")
		FoNHealthChangeEvent HealthChangeEvent;

	void OnHealthAttributeChanged(const FOnAttributeChangeData& Data);

	void OnMoveSpeedAttributeChanged(const FOnAttributeChangeData& Data);

	UFUNCTION(BlueprintCallable,Category="Deid")
		void Died();

	void DestroyTimer();
};
