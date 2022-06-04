// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbilityTargetActor.h"
#include "AbilityChibakuTenseiTargetActor.generated.h"

/**
 * 
 */
UCLASS()
class ABILITYSTUDYDEMO_API AAbilityChibakuTenseiTargetActor : public AGameplayAbilityTargetActor
{
	GENERATED_BODY()

public:

	AAbilityChibakuTenseiTargetActor();

	
	virtual void StartTargeting(UGameplayAbility* Ability) override;

	virtual void ConfirmTargetingAndContinue() override;

	virtual void Tick(float DeltaSeconds) override;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Ability Settings",meta=(ExposeOnSpawn=true))
	float Radius;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Ability Settings",meta=(ExposeOnSpawn=true))
	TSubclassOf<AActor> ConePointClass;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Ability Settings",meta=(ExposeOnSpawn=true))
	TSubclassOf<AActor> MeteorClass;

	UFUNCTION(BlueprintCallable,Category="Chikabu Tensi")
	bool GetPlayerLookingPoint(FVector& LookingPoint);


protected:
	UPROPERTY()
	AActor* ConePoint;

	UPROPERTY()
	AActor* Meteor;
	
};
