// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterBase.h"
#include "MultiFPSDemo1/Weapons/WeaponBaseServer.h"
#include "MultiFPSDemo1/Weapons/WeaponBaseClient.h"
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

	StartWithKindOfWeapon();
	
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

	PlayerInputComponent->BindAction(TEXT("Fire"),IE_Pressed,this,&ACharacterBase::InputFireWeaponPressed);
	PlayerInputComponent->BindAction(TEXT("Fire"),IE_Released,this,&ACharacterBase::InputFireWeaponReleased);
	
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

void ACharacterBase::ClientEquipWeaponParimary_Implementation()
{
	if(Server_PrimaryWeapon!=nullptr)
	{
		FActorSpawnParameters SpawnParameters;
		SpawnParameters.Owner = this;
		SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		Clinet_PrimaryWeapon = GetWorld()->SpawnActor<AWeaponBaseClient>(Server_PrimaryWeapon->ClientWeaponClass,GetActorTransform(),SpawnParameters);

		if(Clinet_PrimaryWeapon)
		{
			Clinet_PrimaryWeapon->K2_AttachToComponent(FPArmMesh,TEXT("WeaponSocket"),
				EAttachmentRule::SnapToTarget,EAttachmentRule::SnapToTarget,EAttachmentRule::SnapToTarget,true);
		}
	}
}

void ACharacterBase::ClientWeaponFire_Implementation()
{
	AWeaponBaseClient* CurrentClientWeapon=GetCurrentClientWeapon();
	if(CurrentClientWeapon)
	{
		CurrentClientWeapon->PlayFireAnimation();
	}
}

void ACharacterBase::EquipWeapon_Primary(AWeaponBaseServer* CurrWeapon_Server)
{
	if(!Server_PrimaryWeapon)
	{
		if(CurrWeapon_Server!=nullptr)
		{
			Server_PrimaryWeapon = CurrWeapon_Server;
			Server_PrimaryWeapon->SetOwner(this);
			Server_PrimaryWeapon->K2_AttachToComponent(GetMesh(),TEXT("Weapon_Rifle"),
				EAttachmentRule::SnapToTarget,EAttachmentRule::SnapToTarget,EAttachmentRule::SnapToTarget,true);

			ClientEquipWeaponParimary_Implementation();
		}
	}
	
	//if(CurrWeapon)
}

void ACharacterBase::StartWithKindOfWeapon()
{
	if(HasAuthority())
	{
		UClass* BuleprintWeaponClass = StaticLoadClass(AWeaponBaseServer::StaticClass(),nullptr,TEXT("Blueprint'/Game/BluePrints/Weapons/AK47/WeaponServer_Ak47.WeaponServer_Ak47_c'"));
		PurchaseWeapon(BuleprintWeaponClass);
	}
}

void ACharacterBase::PurchaseWeapon(UClass* WeaponClass)
{
	FActorSpawnParameters SpawnParameters;
	SpawnParameters.Owner = this;
	SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	
	if(WeaponClass->IsChildOf(AWeaponBaseServer::StaticClass()))
	{
		AWeaponBaseServer* WeaponServer = GetWorld()->SpawnActor<AWeaponBaseServer>(WeaponClass,GetActorTransform(),SpawnParameters);
		if(WeaponServer!=nullptr)
		{
			WeaponServer->OnEquipWeapon();
			EquipWeapon_Primary(WeaponServer);
		}
	}
}

void ACharacterBase::PrimaryWeapon_Fire()
{
	UE_LOG(LogTemp,Warning,TEXT("PrimaryWeapon_Fire"));

	//Server

	//clinet
	ClientWeaponFire();
	
}

void ACharacterBase::PrimaryWeapon_StopFire()
{
	UE_LOG(LogTemp,Warning,TEXT("PrimaryWeapon_StopFire"));
}

AWeaponBaseClient* ACharacterBase::GetCurrentClientWeapon()
{
	AWeaponBaseClient* TargetWeapon=nullptr;
	
	 if(Clinet_PrimaryWeapon!=nullptr)
	 {
	 	switch(Clinet_PrimaryWeapon->KindOfWeapon)
	 	{
	 		case EWeaponType::AK47:
	 			{
	 				TargetWeapon = Clinet_PrimaryWeapon;
	 			}
	 			break;
	 			
	 		default:
	 			{
	 				
	 			}
	 			break;
	 	}
	 }
	
	 return TargetWeapon;
	
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

void ACharacterBase::InputFireWeaponPressed()
{
	if(!Server_PrimaryWeapon)
		return ;
	switch (Server_PrimaryWeapon->KindOfWeapon)
	{
		case EWeaponType::AK47:
			{
				PrimaryWeapon_Fire();
			}
			break;
	
		default:
			break;
	}
}

void ACharacterBase::InputFireWeaponReleased()
{
	if(!Server_PrimaryWeapon)
		return ;
	
	switch (Server_PrimaryWeapon->KindOfWeapon)
	{
		case EWeaponType::AK47:
			{
				PrimaryWeapon_StopFire();
			}
			break;
		
		default:
			break;
	}
}

