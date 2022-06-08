// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "C_BaseChar.h"
#include "Perception/AISenseConfig_Sight.h"

#include "C_AIChar.generated.h"

/**
 * 
 */
UCLASS()
class GTX6_API AC_AIChar : public AC_BaseChar
{
	GENERATED_BODY()

public:

	AC_AIChar();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Custom")
		class UAIPerceptionComponent* AIPerception;
	

	UFUNCTION()
		void OnTargetPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Custom")
		class UBehaviorTree* BT_AI;

	UFUNCTION(BlueprintImplementableEvent)
		void Setting_NormalMood();

	UFUNCTION(BlueprintImplementableEvent)
		void Setting_AngrylMood();

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

protected:
	virtual void BeginPlay() override;

};
