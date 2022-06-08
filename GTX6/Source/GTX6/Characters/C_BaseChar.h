// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "C_BaseChar.generated.h"


USTRUCT(BlueprintType)
struct FHandCombatPair
{
	GENERATED_BODY()


public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		class UAnimMontage* AttackerMontage;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		class UAnimMontage* ReceiveMontage;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		float DistanceBetweenAnimation = 100.0f;

};

UCLASS()
class GTX6_API AC_BaseChar : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AC_BaseChar();

	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	class USpringArmComponent* SpringArm;

	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	class UCameraComponent* Camera;

	//UPROPERTY(BlueprintReadWrite, EditAnywhere)
	//	class USphereComponent* punchCollisionL;

	//UPROPERTY(BlueprintReadWrite, EditAnywhere)
	//	class USphereComponent* punchCollisionR;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

	UFUNCTION(BlueprintCallable)
		bool ISCombat();

	UFUNCTION()
		void GrenadePressed();
	UFUNCTION()
		void GrenadeReleased();

	UFUNCTION()
		void DestroySplineMeshs();

	void Scrolling(int value);

	void Attacking();

	void AddGun(class AC_PickUpBase* NearByGun);

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		TArray<TSubclassOf<class AC_PickUpBase>> A_Guns;

	int Gun_Using_Index = -1;   // not 
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		class AC_PickUpBase* GunSing;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		int Health = 100;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		TArray<UAnimSequence*> DealthAnimations;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		TArray<USkeletalMesh*> SM_Chars;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		bool bIsAlive = true;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		bool IsGrenade=false;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		FVector LaunchVelocity;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		UStaticMesh* SM_Spline;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		TArray<class USplineMeshComponent*> GrenadeSplineMeshs;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		class USplineComponent* GrenadeSpline;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		TSubclassOf<class AC_GrenadeBase> GrenadeClass;

	//hand combat
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		TArray<class UAnimMontage*> SoloPunches;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		bool IsHandCombat;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		TArray<FHandCombatPair> HandCombatPairs;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		int TeamNum;
	//end hand

private:
	void PressedJump();

	void MoveForward(float value);
	void MoveRight(float value);
	void LookUp(float value);
	void LookRight(float value);

	void Sroll_Up();
	
	void Sroll_Down();

	void ChangeChar();

	void SprintPressed();

	void SprintReleased();

	void SetTeamNum(int TeamNumValue);
	
	int GetTeamNum();

	void EndMontageCombat();

	//hand combat
	UFUNCTION()
		void HandCombatSpherOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	//end hand combat

};
