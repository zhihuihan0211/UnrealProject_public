// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Particles/ParticleSystem.h"
#include "sound/SoundCue.h"
#include "C_PickUpBase.generated.h"

UCLASS()
class GTX6_API AC_PickUpBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AC_PickUpBase();

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Defaults")
		class USkeletalMeshComponent* SK_Gun;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Defaults")
		class USphereComponent* SC_PickUP;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Defaults")
		class UWidgetComponent* InfoWidget;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Defaults")
		UParticleSystem* PS_Muzzle;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Defaults")
		USoundCue* SC_Fire;

	void RemoveComponets();


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void SetInfoWidgetVisibility(bool bIsActive);


private:

	class AC_BaseChar* PlaingChar;

	void PickUp();

	UFUNCTION()
		void SC_OverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		void SC_OverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	//UFUNCTION()
};
 