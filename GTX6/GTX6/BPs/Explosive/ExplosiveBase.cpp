// Fill out your copyright notice in the Description page of Project Settings.


#include "ExplosiveBase.h"
#include "Kismet/GameplayStatics.h"
#include "GTX6/Extras/MUtils.h"
#include "GTX6/Pickups/GrenadeDamageType.h"

// Sets default values
AExplosiveBase::AExplosiveBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	SM_BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SM_BaseMesh"));
	SM_BaseMesh->SetupAttachment(RootComponent);
	// SM_BaseMesh

}

// Called when the game starts or when spawned
void AExplosiveBase::BeginPlay()
{
	Super::BeginPlay();
	
}

float AExplosiveBase::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	if(!PS_Explosive || !SB_ExplosiveSound)
		return 0;

	FVector loc = GetActorLocation() + GetActorForwardVector() * 200;
	TArray<AActor*> ignoredActos;
	ignoredActos.Add(this);

	UGameplayStatics::ApplyRadialDamageWithFalloff(GetWorld(),100,20, loc,500,1000,30, UGrenadeDamageType::StaticClass(), ignoredActos);
	UGameplayStatics::SpawnSoundAtLocation(GetWorld(),SB_ExplosiveSound,GetActorLocation());
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), PS_Explosive, GetActorLocation(),FRotator::ZeroRotator);
	
	Destroy();
	MUtils::PM("I am blasting something!");
	
	return 0.0f;
}


