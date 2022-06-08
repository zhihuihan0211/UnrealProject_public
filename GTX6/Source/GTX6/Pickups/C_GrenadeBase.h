// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "C_GrenadeBase.generated.h"

UCLASS()
class GTX6_API AC_GrenadeBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AC_GrenadeBase();

	//class UStaticMesh
	UPROPERTY(EditAnywhere,Category="Custom")
		class UStaticMeshComponent* SM_Grenade;

	UPROPERTY(EditAnywhere, Category = "Custom")
		class UParticleSystem* PS_GrenadeExplode;

	UPROPERTY(EditAnywhere, Category = "Custom")
		class USoundBase* SB_GrenadeSound;

private:

	UFUNCTION()
		void MakeBlast();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
