// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectExecutionCalculation.h"
#include "AttributeSetBase.h"
#include "UGEDamageExecutionCalculation.generated.h"

struct SDamageStatics
{
	DECLARE_ATTRIBUTE_CAPTUREDEF(Damage);
	DECLARE_ATTRIBUTE_CAPTUREDEF(Armor);
	DECLARE_ATTRIBUTE_CAPTUREDEF(Health);
	SDamageStatics()
	{
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAttributeSetBase,Damage,Source,true);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAttributeSetBase,Armor,Source,true);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAttributeSetBase,Health,Source,true);
	}
};

static const SDamageStatics& DamageStatics()
{
	static SDamageStatics DamageStatics;
	return  DamageStatics;
}


/**
 * 
 */
UCLASS()
class ABILITYSTUDYDEMO_API UUGEDamageExecutionCalculation : public UGameplayEffectExecutionCalculation
{
	GENERATED_BODY()

public:
	UUGEDamageExecutionCalculation();

	virtual void Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const override;;
	
};
