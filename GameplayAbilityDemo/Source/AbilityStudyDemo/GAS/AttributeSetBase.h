// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "AttributeSetBase.generated.h"


#define ATTRIBUTE_ACCESSORS(ClassName,PropertyName) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName,PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

/**
 * 
 */
// DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnAttributeChangedDelegate, float, Health, float, MaxHealth);

UCLASS()
class ABILITYSTUDYDEMO_API UAttributeSetBase : public UAttributeSet
{
	GENERATED_BODY()

public:
	UAttributeSetBase();

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	//Health
	UPROPERTY(VisibleAnywhere,BlueprintReadWrite,Category="Attribute", ReplicatedUsing=OnRep_Health)
		FGameplayAttributeData Health;
	ATTRIBUTE_ACCESSORS(UAttributeSetBase,Health);

	UPROPERTY(VisibleAnywhere,BlueprintReadWrite,Category="Attribute", ReplicatedUsing=OnRep_MaxHealth)
		FGameplayAttributeData MaxHealth;
	ATTRIBUTE_ACCESSORS(UAttributeSetBase, MaxHealth);

	//Mana
	UPROPERTY(VisibleAnywhere,BlueprintReadWrite,Category="Attribute",ReplicatedUsing=OnRep_Mana)
		FGameplayAttributeData Mana;
	ATTRIBUTE_ACCESSORS(UAttributeSetBase,Mana);

	//speed
	UPROPERTY(VisibleAnywhere,BlueprintReadWrite,Category="Attribute",ReplicatedUsing=OnRep_MoveSpeed)
		FGameplayAttributeData MoveSpeed;
	ATTRIBUTE_ACCESSORS(UAttributeSetBase,MoveSpeed);

	//Attack 
	UPROPERTY(VisibleAnywhere,BlueprintReadWrite,Category="Attribute",ReplicatedUsing=OnRep_Damage)
	FGameplayAttributeData Damage;
	ATTRIBUTE_ACCESSORS(UAttributeSetBase,Damage);

	UPROPERTY(VisibleAnywhere,BlueprintReadWrite,Category="Attribute",ReplicatedUsing=OnRep_Armor)
	FGameplayAttributeData Armor;
	ATTRIBUTE_ACCESSORS(UAttributeSetBase,Armor);


	virtual  void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;

	virtual void PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData &Data) override;

	// UPROPERTY(BlueprintAssignable)
	// 	FOnAttributeChangedDelegate OnHealthChanged;

	UFUNCTION()
	virtual void OnRep_Health(const FGameplayAttributeData& OldHealth);

	UFUNCTION()
	virtual void OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth);

	UFUNCTION()
	virtual void OnRep_Mana(const FGameplayAttributeData& oldMana);

	UFUNCTION()
	virtual void OnRep_MoveSpeed(const FGameplayAttributeData& oldSpeed);

	UFUNCTION()
	virtual void OnRep_Damage(const FGameplayAttributeData& oldDamage);
	
	UFUNCTION()
	virtual void OnRep_Armor(const FGameplayAttributeData& oldArmor);

	
};
