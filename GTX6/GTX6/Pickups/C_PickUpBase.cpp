// Fill out your copyright notice in the Description page of Project Settings.


#include "C_PickUpBase.h"
#include "Components/SphereComponent.h"
#include "Components/WidgetComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "../Characters/C_BaseChar.h"

// Sets default values
AC_PickUpBase::AC_PickUpBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SK_Gun = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SK_GUN"));
	SK_Gun->SetupAttachment(RootComponent);

	SC_PickUP = CreateDefaultSubobject<USphereComponent>(TEXT("SC_PickUP"));
	SC_PickUP->SetupAttachment(SK_Gun);
	SC_PickUP->SetSphereRadius(100);
	SC_PickUP->OnComponentBeginOverlap.AddDynamic(this, &AC_PickUpBase::SC_OverlapBegin);
	SC_PickUP->OnComponentEndOverlap.AddDynamic(this, &AC_PickUpBase::SC_OverlapEnd);

	InfoWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("Info_Widget"));
	InfoWidget->SetupAttachment(SK_Gun);
	InfoWidget->SetVisibility(false);

	InputComponent = CreateDefaultSubobject<UInputComponent>(TEXT("Input Component"));
	InputComponent->BindAction("Interact",IE_Pressed,this,&AC_PickUpBase::PickUp);
}

void AC_PickUpBase::RemoveComponets()
{
	SC_PickUP->DestroyComponent();
	InfoWidget->DestroyComponent();
}

void AC_PickUpBase::PickUp()
{
	//PlaingChar->AddGun(this);
	UE_LOG(LogTemp, Warning, TEXT("Picking up the gun!"));
	PlaingChar->AddGun(this);
}

// Called when the game starts or when spawned
void AC_PickUpBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AC_PickUpBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AC_PickUpBase::SC_OverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//UE_LOG(Log)
	PlaingChar = Cast<AC_BaseChar>(OtherActor);

	if (!PlaingChar)
		return;
	
	InfoWidget->SetVisibility(true);
	EnableInput(GetWorld()->GetFirstPlayerController());
	UE_LOG(LogTemp, Warning,TEXT("i am overlaping"));
}

void AC_PickUpBase::SC_OverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	InfoWidget->SetVisibility(false);
	DisableInput(GetWorld()->GetFirstPlayerController());
	UE_LOG(LogTemp, Warning, TEXT("i am end overlap"));
}

void AC_PickUpBase::SetInfoWidgetVisibility(bool bIsActive)
{
	if (bIsActive)
	{
		EnableInput(GetWorld()->GetFirstPlayerController());
	}
	else
	{
		DisableInput(GetWorld()->GetFirstPlayerController());
	}
	InfoWidget->SetVisibility(bIsActive);
}

