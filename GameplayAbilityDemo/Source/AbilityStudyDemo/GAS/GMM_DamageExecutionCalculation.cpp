// Fill out your copyright notice in the Description page of Project Settings.


#include "GMM_DamageExecutionCalculation.h"

UGMM_DamageExecutionCalculation::UGMM_DamageExecutionCalculation()
{
	RelevantAttributesToCapture.Add(DamageStatics().DamageDef);
	RelevantAttributesToCapture.Add(DamageStatics().ArmorDef);
	
}

float UGMM_DamageExecutionCalculation::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
{

	const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* TargetTags = Spec.CapturedSourceTags.GetAggregatedTags();

	FAggregatorEvaluateParameters EvaluateParameters;
	EvaluateParameters.SourceTags = SourceTags;
	EvaluateParameters.TargetTags = TargetTags;

	float Damage = 0.0f;
	float Armor = 0.0f;
	
	bool IsGetDamage = GetCapturedAttributeMagnitude(DamageStatics().DamageDef,Spec,EvaluateParameters,Damage);
	bool IsGetArmor = GetCapturedAttributeMagnitude(DamageStatics().ArmorDef,Spec,EvaluateParameters,Armor);

	if(IsGetDamage)
	{
		return Damage - Armor;
	}

	return 0;
	// return Super::CalculateBaseMagnitude_Implementation(Spec);
}
