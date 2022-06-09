// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/Character.h"
#include "CharacterBase.generated.h"

UCLASS()
class MULTIFPSDEMO1_API ACharacterBase : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACharacterBase();

private:
	UPROPERTY(Category=Character, VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	UCameraComponent* PlayerCamera;

	UPROPERTY(Category=Character, VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	USkeletalMeshComponent*	FPArmMesh;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	void MoveForward(float AxisValue);
	
	void MoveRight(float AxisValue);
	
	void Turn(float AxisValue);
	
	void LookUp(float AxisValue);
	
	void JumpStart();
	void JumpStop();

	void SlowSpeedWalkAction();
	void NormalSpeedWalkAction();

	

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


#pragma region NetWalk
	
public:
	UFUNCTION(Server,Reliable,WithValidation)
	void ServerSlowSpeedWalkAction();
	void ServerSlowSpeedWalkAction_Implementation();
	bool ServerSlowSpeedWalkAction_Validate();
	
	UFUNCTION(Server,Reliable,WithValidation)
	void ServerNormalSpeedWalkAction();
	void ServerNormalSpeedWalkAction_Implementation();
	bool ServerNormalSpeedWalkAction_Validate();

#pragma endregion 
	
};
