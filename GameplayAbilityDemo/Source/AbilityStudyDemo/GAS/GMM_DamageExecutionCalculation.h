// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectExecutionCalculation.h"
#include "GameplayModMagnitudeCalculation.h"
#include "AttributeSetBase.h"
#include "GMM_DamageExecutionCalculation.generated.h"


/*
 * 
 */
struct  SDamageStatics
{
	DECLARE_ATTRIBUTE_CAPTUREDEF(Damage);
	DECLARE_ATTRIBUTE_CAPTUREDEF(Armor);

	SDamageStatics()
	{
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAttributeSetBase,Damage,Source,true);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAttributeSetBase,Armor,Source,true);
	}
	
};

static const SDamageStatics& DamageStatics()
{
	static SDamageStatics DStatics;
	return  DStatics;
}


/**
 * 
 */
UCLASS()
class ABILITYSTUDYDEMO_API UGMM_DamageExecutionCalculation : public UGameplayModMagnitudeCalculation
{
	GENERATED_BODY()

public:
	UGMM_DamageExecutionCalculation();

	virtual float CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const override;
	
};
