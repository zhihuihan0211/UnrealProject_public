// Fill out your copyright notice in the Description page of Project Settings.


#include "C_GrenadeBase.h"
#include "Kismet/GameplayStatics.h"
#include "GrenadeDamageType.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
AC_GrenadeBase::AC_GrenadeBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SM_Grenade = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SM_Grenade"));
	SM_Grenade->SetupAttachment(RootComponent);
	SM_Grenade->SetSimulatePhysics(true);



}

// Called when the game starts or when spawned
void AC_GrenadeBase::BeginPlay()
{
	Super::BeginPlay();
	
	FTimerHandle timer;
	AActor::GetWorldTimerManager().SetTimer(timer, this, &AC_GrenadeBase::MakeBlast, 5, false);
}

void AC_GrenadeBase::MakeBlast()
{
	TArray<AActor*> IgnoreActor;
	UGameplayStatics::ApplyRadialDamageWithFalloff(GetWorld(), 100, 20, SM_Grenade->GetComponentLocation(), 500, 1000, 30, UGrenadeDamageType::StaticClass(), IgnoreActor);
	UGameplayStatics::SpawnSoundAtLocation(GetWorld(), SB_GrenadeSound, SM_Grenade->GetComponentLocation());
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), PS_GrenadeExplode, SM_Grenade->GetComponentLocation(),FRotator::ZeroRotator);
	UE_LOG(LogTemp,Warning,TEXT("I am blast !"));
}

// Called every frame
void AC_GrenadeBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

