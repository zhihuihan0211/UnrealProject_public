// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WeaponBaseServer.h"
#include "GameFramework/Actor.h"

#include "WeaponBaseClient.generated.h"

UCLASS()
class MULTIFPSDEMO1_API AWeaponBaseClient : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWeaponBaseClient();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USkeletalMeshComponent* WeaponMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class AWeaponBaseServer* weaponServer;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EWeaponType KindOfWeapon;


	UFUNCTION(BlueprintImplementableEvent,Category="WeaponFire")
	void PlayFireAnimation();
	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
