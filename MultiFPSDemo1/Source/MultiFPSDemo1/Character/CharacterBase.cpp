// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterBase.h"

#include "Camera/CameraAnim.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
ACharacterBase::ACharacterBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PlayerCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("PlayerCamera"));
	PlayerCamera->SetupAttachment(RootComponent);
	PlayerCamera->bUsePawnControlRotation=true;

	FPArmMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("FPArmMesh"));
	FPArmMesh->SetupAttachment(PlayerCamera);
	FPArmMesh->SetOnlyOwnerSee(true);
	
}

// Called when the game starts or when spawned
void ACharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
}



// Called every frame
void ACharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ACharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction(TEXT("SlowSpeedWalk"),IE_Pressed,this,&ACharacterBase::SlowSpeedWalkAction);
	PlayerInputComponent->BindAction(TEXT("SlowSpeedWalk"),IE_Released,this,&ACharacterBase::NormalSpeedWalkAction);
	
	PlayerInputComponent->BindAction(TEXT("Jump"),IE_Pressed,this,&ACharacterBase::JumpStart);
	PlayerInputComponent->BindAction(TEXT("Jump"),IE_Released,this,&ACharacterBase::JumpStop);
	
	PlayerInputComponent->BindAxis(TEXT("MoveForward"),this, &ACharacterBase::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("MoveRight"),this, &ACharacterBase::MoveRight);
	PlayerInputComponent->BindAxis(TEXT("Turn"),this, &ACharacterBase::Turn);
	PlayerInputComponent->BindAxis(TEXT("LookUp"),this, &ACharacterBase::LookUp);


}

void ACharacterBase::ServerSlowSpeedWalkAction_Implementation()
{
	GetCharacterMovement()->MaxWalkSpeed = 300.0f;
}

bool ACharacterBase::ServerSlowSpeedWalkAction_Validate()
{
	return true;
}

void ACharacterBase::ServerNormalSpeedWalkAction_Implementation()
{
	GetCharacterMovement()->MaxWalkSpeed = 600.0f;
}

bool ACharacterBase::ServerNormalSpeedWalkAction_Validate()
{
	return true;

}

void ACharacterBase::MoveForward(float AxisValue)
{
	AddMovementInput(GetActorForwardVector(), AxisValue);
}

void ACharacterBase::MoveRight(float AxisValue)
{
	AddMovementInput(GetActorRightVector(), AxisValue);
}

void ACharacterBase::Turn(float AxisValue)
{
	AddControllerYawInput(AxisValue);
}

void ACharacterBase::LookUp(float AxisValue)
{
	AddControllerPitchInput(AxisValue);
}

void ACharacterBase::JumpStart()
{
	Jump();
}

void ACharacterBase::JumpStop()
{
	StopJumping();
}

void ACharacterBase::SlowSpeedWalkAction()
{
	GetCharacterMovement()->MaxWalkSpeed = 300.0f;
	ServerSlowSpeedWalkAction();
}

void ACharacterBase::NormalSpeedWalkAction()
{
	GetCharacterMovement()->MaxWalkSpeed = 600.0f;
	ServerNormalSpeedWalkAction();
}

