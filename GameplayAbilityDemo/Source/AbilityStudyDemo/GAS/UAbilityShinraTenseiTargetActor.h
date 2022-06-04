// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbilityTargetActor.h"
#include "UAbilityShinraTenseiTargetActor.generated.h"

/**
 * 
 */
UCLASS()
class ABILITYSTUDYDEMO_API AUAbilityShinraTenseiTargetActor : public AGameplayAbilityTargetActor
{
	GENERATED_BODY()

public:
	AUAbilityShinraTenseiTargetActor();


	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Ability Settings",meta=(ExposeOnSpawn=true))
	float Radius;
	

	virtual void StartTargeting(UGameplayAbility* Ability) override;

	virtual void ConfirmTargeting() override;

	
	
};
