// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"


#include "ExplosiveBase.generated.h"


UCLASS()
class GTX6_API AExplosiveBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AExplosiveBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;



public:	

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UStaticMeshComponent* SM_BaseMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UParticleSystem* PS_Explosive;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class USoundBase* SB_ExplosiveSound;

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

};
