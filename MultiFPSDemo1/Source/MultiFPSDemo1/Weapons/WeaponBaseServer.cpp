// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponBaseServer.h"

#include "MultiFPSDemo1/Character/CharacterBase.h"

// Sets default values
AWeaponBaseServer::AWeaponBaseServer()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WeaponMesh"));
	RootComponent = WeaponMesh;
	SphereComponent = CreateDefaultSubobject<USphereComponent>("SphereComponent");
	SphereComponent->SetupAttachment(WeaponMesh);

	WeaponMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	WeaponMesh->SetCollisionObjectType(ECollisionChannel::ECC_WorldStatic);

	SphereComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	SphereComponent->SetCollisionObjectType(ECollisionChannel::ECC_WorldDynamic);

	WeaponMesh->SetOwnerNoSee(true);
	WeaponMesh->SetEnableGravity(true);
	WeaponMesh->SetSimulatePhysics(true);

	SphereComponent->OnComponentBeginOverlap.AddDynamic(this,&AWeaponBaseServer::OnOtherBeginOverlap);

	SetReplicates(true);

}

void AWeaponBaseServer::OnOtherBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ACharacterBase* CurrCharacter;
	
	CurrCharacter = Cast<ACharacterBase>(OtherActor);
	if(CurrCharacter!=nullptr)
	{
		OnEquipWeapon();
		CurrCharacter->EquipWeapon_Primary(this);
	}
	
}

void AWeaponBaseServer::OnEquipWeapon()
{
	WeaponMesh->SetEnableGravity(false);
	WeaponMesh->SetSimulatePhysics(false);
	WeaponMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	SphereComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

// Called when the game starts or when spawned
void AWeaponBaseServer::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AWeaponBaseServer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

