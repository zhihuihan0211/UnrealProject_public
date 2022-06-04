// Fill out your copyright notice in the Description page of Project Settings.


#include "AttributeSetBase.h"
#include "GameplayEffectExtension.h"
#include "GameplayEffect.h"
#include "Net/UnrealNetwork.h"
// #include "UE_LO"

UAttributeSetBase::UAttributeSetBase()
{
	Health = 100.0f;
	MaxHealth = 100.0f;
}

void UAttributeSetBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME_CONDITION_NOTIFY(UAttributeSetBase,Health,COND_None,REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAttributeSetBase,MaxHealth,COND_None,REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAttributeSetBase,Mana,COND_None,REPNOTIFY_Always);

	DOREPLIFETIME_CONDITION_NOTIFY(UAttributeSetBase,MoveSpeed,COND_None,REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAttributeSetBase,Damage,COND_None,REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAttributeSetBase,Armor,COND_None,REPNOTIFY_Always);

}

void UAttributeSetBase::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);
}

void UAttributeSetBase::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	if(Data.EvaluatedData.Attribute.GetUProperty()==FindFieldChecked<FProperty>(UAttributeSetBase::StaticClass(),GET_MEMBER_NAME_CHECKED(UAttributeSetBase,Health) ))
	{
		Health.SetCurrentValue(FMath::Clamp(Health.GetCurrentValue(),0.0f,MaxHealth.GetBaseValue() ));		

		UE_LOG(LogTemp,Warning,TEXT("Current Health = %f"),Health.GetCurrentValue());
		// OnHealthChanged.Broadcast(Health.GetCurrentValue(),MaxHealth.GetCurrentValue());
	}
}

void UAttributeSetBase::OnRep_Health(const FGameplayAttributeData& OldHealth)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAttributeSetBase,Health,OldHealth);
}

void UAttributeSetBase::OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAttributeSetBase,MaxHealth,OldMaxHealth);
}

void UAttributeSetBase::OnRep_Mana(const FGameplayAttributeData& oldMana)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAttributeSetBase,Mana,oldMana);
}

void UAttributeSetBase::OnRep_MoveSpeed(const FGameplayAttributeData& oldSpeed)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAttributeSetBase,Mana,oldSpeed);
}

void UAttributeSetBase::OnRep_Damage(const FGameplayAttributeData& oldDamage)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAttributeSetBase,Mana,oldDamage);

}

void UAttributeSetBase::OnRep_Armor(const FGameplayAttributeData& oldArmor)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAttributeSetBase,Mana,oldArmor);
}

