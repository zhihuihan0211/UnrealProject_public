// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Tasks/AbilityTask.h"
#include "AT_AttributeChange.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FAttributeChange,FGameplayAttribute,Attribute,float,NewValue,float,OldValue);
/**
 * 
 */
UCLASS()
class ABILITYSTUDYDEMO_API UAT_AttributeChange : public UAbilityTask
{
	GENERATED_BODY()


public:
	UAT_AttributeChange(const FObjectInitializer& ObjectInitializer);

	virtual  void Activate() override;

	UPROPERTY(BlueprintAssignable)
	FAttributeChange AttributeChange;

	// eta=(HidePin="OwningAbility", DefaultToSelf="OwningAbility", BlueprintInternalUseOnly="TRUE"))
	UFUNCTION(BlueprintCallable,Category="Ability|Tasks",meta=(HidePin="OwningAbility",DefaultToSelf="OwningAbility",BlueprintInternalUseOnly="True"))
	static UAT_AttributeChange* ListenForAttributeChange(UGameplayAbility* OwningAbility,bool TriggerOnce,UAbilitySystemComponent* SystemComponent ,FGameplayAttribute Attribute);

protected:
	bool TriggerOnce;
	
	FGameplayAttribute Attribute;
	
	void OnAttributeChanged(const FOnAttributeChangeData& Data);

	virtual void OnDestroy(bool bInOwnerFinished) override;

	
};
