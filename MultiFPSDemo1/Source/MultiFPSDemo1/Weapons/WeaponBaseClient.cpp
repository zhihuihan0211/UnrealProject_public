// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponBaseClient.h"

// Sets default values
AWeaponBaseClient::AWeaponBaseClient()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WeaponMesh"));
	RootComponent = WeaponMesh;
	WeaponMesh->SetOnlyOwnerSee(true);

}

// Called when the game starts or when spawned
void AWeaponBaseClient::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AWeaponBaseClient::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

