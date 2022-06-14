// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
// #include "WeaponBaseClient.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Actor.h"
#include "WeaponBaseServer.generated.h"

UENUM()
enum class EWeaponType : uint8 
{
	AK47 UMETA(DisplayName="AK47"),
	DesertEagle UMETA(DisplayName=“DesertEagle”)
};


UCLASS()
class MULTIFPSDEMO1_API AWeaponBaseServer : public AActor
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EWeaponType KindOfWeapon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USkeletalMeshComponent* WeaponMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USphereComponent* SphereComponent;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TSubclassOf<class AWeaponBaseClient> ClientWeaponClass;
	

public:	
	// Sets default values for this actor's properties
	AWeaponBaseServer();

	UFUNCTION()
	void OnOtherBeginOverlap( UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	UFUNCTION()
	void OnEquipWeapon();
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
