// Fill out your copyright notice in the Description page of Project Settings.


#include "C_BaseChar.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "../Pickups/C_PickUpBase.h"
#include "Kismet/GameplayStatics.h"
#include "../Extras/MUtils.h"
#include "Animation/AnimSequence.h"
#include "Engine/SkeletalMesh.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/SplineComponent.h"
#include "Components/SplineMeshComponent.h"
#include "Components/SphereComponent.h"
#include "../Pickups/C_GrenadeBase.h"
#include "Kismet/KismetMathLibrary.h"
#include "GTX6/Characters/C_AIChar.h"


// Sets default values
AC_BaseChar::AC_BaseChar()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(RootComponent);

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("FllowCamera"));
	Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);
	GetCharacterMovement()->MaxWalkSpeed = 300.0f;


	//punchCollisionL = CreateDefaultSubobject<USphereComponent>(TEXT("punchCollisionL"));
	//punchCollisionL->SetupAttachment(GetMesh());
	//punchCollisionL->AttachToComponent(GetMesh(), FAttachmentTransformRules(EAttachmentRule::KeepRelative, false), FName("index_01_l"));
	//punchCollisionL->SetRelativeScale3D(FVector(0.2));
	//punchCollisionL->OnComponentBeginOverlap.AddDynamic(this,&AC_BaseChar::HandCombatSpherOverlap);

	//punchCollisionR = CreateDefaultSubobject<USphereComponent>(TEXT("punchCollisionR"));
	//punchCollisionR->SetupAttachment(GetMesh());
	//punchCollisionR->AttachToComponent(GetMesh(), FAttachmentTransformRules(EAttachmentRule::KeepRelative, false), FName("index_01_r"));
	//punchCollisionR->SetRelativeScale3D(FVector(0.2));
	//punchCollisionR->OnComponentBeginOverlap.AddDynamic(this, &AC_BaseChar::HandCombatSpherOverlap);


}

// Called when the game starts or when spawned
void AC_BaseChar::BeginPlay()
{
	Super::BeginPlay();
	ChangeChar();

}

void AC_BaseChar::ChangeChar()
{
	if (SM_Chars.Num() > 0)
		GetMesh()->SetSkeletalMesh(SM_Chars[FMath::RandRange(0, SM_Chars.Num() - 1)]);
}

// Called every frame
void AC_BaseChar::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (IsGrenade)
	{
		if (!SM_Spline)
			return;
		FHitResult OutHit;
		TArray<FVector> OutPathPositions;
		FVector LastTraceDestination;
		FVector StartPos = GetMesh()->GetSocketLocation(FName("rifle_gun_hold_r"));
		LaunchVelocity = Camera->GetForwardVector() + Camera->GetForwardVector() * 2000;

		TArray<AActor*> IgnoredActorArray;
		IgnoredActorArray.Add(this);

		DestroySplineMeshs();
		UGameplayStatics::Blueprint_PredictProjectilePath_ByTraceChannel(GetWorld(), OutHit, OutPathPositions,LastTraceDestination, StartPos, 
			LaunchVelocity, false, 20, ECollisionChannel::ECC_Visibility, false, IgnoredActorArray, EDrawDebugTrace::None, 0);

		if(GrenadeSpline)
			GrenadeSpline->SetSplinePoints(OutPathPositions, ESplineCoordinateSpace::World);

		int Count = FMath::TruncToInt(GrenadeSpline->GetSplineLength() / 100);
		for (int i = 0; i < Count; i++)
		{
			USplineMeshComponent* sMesh = NewObject<USplineMeshComponent>(this, USplineMeshComponent::StaticClass());
			sMesh->SetStaticMesh(SM_Spline);
			sMesh->SetForwardAxis(ESplineMeshAxis::Z);
			sMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
			sMesh->SetStartScale(FVector2D(0.1, 0.1));
			sMesh->SetEndScale(FVector2D(0.1, 0.1));
			sMesh->RegisterComponentWithWorld(GetWorld());
			FVector startp = GrenadeSpline->GetLocationAtDistanceAlongSpline(100 * i, ESplineCoordinateSpace::World);
			FVector startTan = GrenadeSpline->GetTangentAtDistanceAlongSpline(100 * i, ESplineCoordinateSpace::World);
			FVector endp = GrenadeSpline->GetLocationAtDistanceAlongSpline(100 * (i+1), ESplineCoordinateSpace::World);
			FVector endTan = GrenadeSpline->GetTangentAtDistanceAlongSpline(100 * (i+1), ESplineCoordinateSpace::World);
			sMesh->SetStartAndEnd(startp, startTan, endp, endTan);			
			GrenadeSplineMeshs.Add(sMesh);
			
		}

	}
}

void AC_BaseChar::DestroySplineMeshs()
{
	for (USplineMeshComponent* var : GrenadeSplineMeshs)
	{
		if(var)
			var->DestroyComponent();
	}
}

// Called to bind functionality to input
void AC_BaseChar::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	//MoveForward MoveRight LookUp Turn
	PlayerInputComponent->BindAxis(FName("MoveForward"), this, &AC_BaseChar::MoveForward);
	PlayerInputComponent->BindAxis(FName("MoveRight"), this, &AC_BaseChar::MoveRight);
	PlayerInputComponent->BindAxis(FName("LookUp"), this, &AC_BaseChar::LookUp);
	PlayerInputComponent->BindAxis(FName("Turn"), this, &AC_BaseChar::LookRight);

	PlayerInputComponent->BindAction(FName("Jump"), IE_Pressed, this, &AC_BaseChar::PressedJump);

	PlayerInputComponent->BindAction(FName("Scroll_Up"), IE_Pressed, this, &AC_BaseChar::Sroll_Up);
	PlayerInputComponent->BindAction(FName("Scroll_Down"), IE_Pressed, this, &AC_BaseChar::Sroll_Down);

	PlayerInputComponent->BindAction(FName("Attack"), IE_Pressed, this, &AC_BaseChar::Attacking);

	PlayerInputComponent->BindAction(FName("ChangeChar"), IE_Pressed, this, &AC_BaseChar::ChangeChar);

	PlayerInputComponent->BindAction(FName("Sprint"), IE_Pressed, this, &AC_BaseChar::SprintPressed);
	PlayerInputComponent->BindAction(FName("Sprint"), IE_Released, this, &AC_BaseChar::SprintReleased);

	PlayerInputComponent->BindAction(FName("Grenade"), IE_Pressed, this, &AC_BaseChar::GrenadePressed);
	PlayerInputComponent->BindAction(FName("Grenade"), IE_Released, this, &AC_BaseChar::GrenadeReleased);


}

void AC_BaseChar::HandCombatSpherOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor == this || !IsHandCombat)
		return;

	MUtils::PM(OtherActor->GetName() + OtherComp->GetName() + " :recieved some damage!");

	UGameplayStatics::ApplyDamage(OtherActor, 100, GetController(), this, UDamageType::StaticClass());
}

float AC_BaseChar::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	Health = FMath::Clamp(int(Health - DamageAmount), 0, 100);

	MUtils::PM("Update health is " + FString::SanitizeFloat(Health));
	if (Health == 0 && bIsAlive)
	{
		//DealthAnimations
		bIsAlive = false;
		GetMesh()->PlayAnimation(DealthAnimations[0],false);
		MUtils::PM("I am dead,don't shoot me anmore");
		FTimerHandle timerHandle;
		//AActor::GetWorldTimerManager().SetTimer(timerHandle,this, &AActor::Destroy, 5.0f, false);
	}

	return 0.0f;
}

void AC_BaseChar::Attacking()
{
	if(!GunSing)
	{
		//float monageLength = PlayAnimMontage(SoloPunches[UKismetMathLibrary::RandomIntegerInRange(0,SoloPunches.Num()-1)] );

		FHitResult hit_Result;
		FVector StartV = GetActorLocation();
		FVector endV = GetActorForwardVector() * 300 + StartV;
		FCollisionQueryParams params = FCollisionQueryParams();

		params.AddIgnoredActor(this);
		GetWorld()->LineTraceSingleByChannel(hit_Result, StartV, endV, ECollisionChannel::ECC_Camera, params);
		if (!hit_Result.IsValidBlockingHit())
			return;

		AC_AIChar* ai_Char = Cast<AC_AIChar>(hit_Result.GetActor());
		if (!ai_Char)
			return;
		MUtils::PM("I am hitting the vaild ai !");

		if (ai_Char->bIsAlive)
		{
			IsHandCombat = true;
			ai_Char->IsHandCombat = true;
			ai_Char->bIsAlive = false;

			DisableInput(UGameplayStatics::GetPlayerController(GetWorld(), 0));
			FRotator PlayerRotation = GetActorRotation();
			PlayerRotation.Add(0,180,0);
			ai_Char->SetActorRotation(PlayerRotation);
			SetActorLocation(ai_Char->GetActorLocation() + ai_Char->GetActorForwardVector() * 100);

			if (HandCombatPairs.Num() <= 0)
				return;

			int RandIndex = UKismetMathLibrary::RandomIntegerInRange(0, HandCombatPairs.Num() - 1);

			ai_Char->GetController()->UnPossess();

			float montagtLength = ai_Char->PlayAnimMontage(HandCombatPairs[RandIndex].ReceiveMontage);
			PlayAnimMontage(HandCombatPairs[RandIndex].AttackerMontage);

			FTimerHandle montageTimeHandle;
			//FTimerHandle montageTimeHandle_AI;

			GetWorldTimerManager().SetTimer(montageTimeHandle, this, &AC_BaseChar::EndMontageCombat, montagtLength, false);
			
			//faild Test
			//ai_Char->GetWorldTimerManager().SetTimer(montageTimeHandle_AI,ai_Char,&AC_BaseChar::EndMontageCombat, montagtLength, false);

		}
	}
	else
	{

		FHitResult hitResult;
		FVector startV = Camera->GetComponentLocation(); // Camera->GetComponentLocation();
		FVector endv = startV + Camera->GetForwardVector() * 10000;

		FCollisionQueryParams params = FCollisionQueryParams();

		params.AddIgnoredActor(this);

		GetWorld()->LineTraceSingleByChannel(hitResult, startV, endv, ECollisionChannel::ECC_GameTraceChannel1, params);
		if (GunSing->SC_Fire)
			MUtils::PlaySoundAtloc(GetWorld(), GunSing->SC_Fire, GetActorLocation(), this);
		//UGameplayStatics::PlaySoundAtLocation(GetWorld(), GunSing->SC_Fire, GetActorLocation());

		if (hitResult.IsValidBlockingHit())
		{
			FTransform transform;
			transform.SetLocation(hitResult.ImpactPoint);
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), GunSing->PS_Muzzle, transform);
			UGameplayStatics::SpawnEmitterAttached(GunSing->PS_Muzzle, GunSing->SK_Gun, FName("MuzzleFlash"),
				FVector::ZeroVector, FRotator::ZeroRotator, EAttachLocation::KeepRelativeOffset);
			MUtils::PM("Current hit bone name is " + hitResult.BoneName.ToString());

			int DamageApply = 10;
			if (hitResult.BoneName.IsEqual(FName("head")))
			{
				DamageApply = 100;
			}
			UGameplayStatics::ApplyDamage(hitResult.GetActor(), DamageApply, GetController(), this, UDamageType::StaticClass());
		}
	}
}

void AC_BaseChar::EndMontageCombat()
{
	IsHandCombat = true;
	EnableInput(UGameplayStatics::GetPlayerController(GetWorld(), 0));


	// faild Test
	//AC_AIChar* ai_Char = Cast<AC_AIChar>(GetOwner());
	//if (ai_Char)
	//{
	//	ai_Char->GetController()->Possess(ai_Char);
	//}
	//else
	//{
	//	IsHandCombat = true;
	//	EnableInput(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	//}
}

bool AC_BaseChar::ISCombat()
{
	if (Gun_Using_Index == -1)
		return false;
	else
		return true;

}

void AC_BaseChar::PressedJump()
{
	Jump();
}

void AC_BaseChar::AddGun(class AC_PickUpBase* NearByGun)
{
	int beforelen = A_Guns.Num();
	int isSuccess = A_Guns.AddUnique(NearByGun->GetClass());
	if(beforelen != A_Guns.Num())
		NearByGun->Destroy();
}

void AC_BaseChar::MoveForward(float value)
{
	APawn::AddMovementInput(GetActorForwardVector(), value);

}
void AC_BaseChar::MoveRight(float value)
{
	APawn::AddMovementInput(GetActorRightVector(), value);

}
void AC_BaseChar::LookUp(float value)
{
	APawn::AddControllerPitchInput(value);
}

void AC_BaseChar::LookRight(float value)
{
	APawn::AddControllerYawInput(value);
}

void AC_BaseChar::Sroll_Up()
{
	Scrolling(1);
}

void AC_BaseChar::Sroll_Down()
{
	Scrolling(-1);
}

void AC_BaseChar::Scrolling(int value)
{
	int PrevIndex = Gun_Using_Index;
	Gun_Using_Index += value;
	Gun_Using_Index = FMath::Clamp(Gun_Using_Index, -1, A_Guns.Num() - 1);
	if (PrevIndex == Gun_Using_Index)
		return;

	if (Gun_Using_Index == -1)
	{
		GunSing->Destroy();
		GunSing = nullptr;
		return;
	}
	if (GunSing != nullptr)
	{
		GunSing->Destroy();
		GunSing = nullptr;
	}

	GunSing = GetWorld()->SpawnActor<AC_PickUpBase>(A_Guns[Gun_Using_Index]);
	//GunSing->SetInfoWidgetVisibility(false);
	GunSing->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, FName("rifle_gun_hold_r"));
	GunSing->RemoveComponets();

}

void AC_BaseChar::SprintPressed()
{
	GetCharacterMovement()->MaxWalkSpeed = 600.0f;

}

void AC_BaseChar::SprintReleased()
{
	GetCharacterMovement()->MaxWalkSpeed = 300.0f;
}

void AC_BaseChar::GrenadePressed()
{
	IsGrenade = true;
	GrenadeSpline = NewObject<USplineComponent>(USplineComponent::StaticClass());
}

void AC_BaseChar::GrenadeReleased()
{
	IsGrenade = false;
	GrenadeSpline->DestroyComponent();
	DestroySplineMeshs();
	
	FVector loc = GetMesh()->GetSocketLocation(TEXT("rifle_gun_hold_r"));

	AC_GrenadeBase* GrenadeObj = GetWorld()->SpawnActor<AC_GrenadeBase>(GrenadeClass, loc, FRotator::ZeroRotator);
	GrenadeObj->SM_Grenade->AddImpulse(LaunchVelocity);
}

void AC_BaseChar::SetTeamNum(int TeamNumValue)
{
	TeamNum = TeamNumValue;
}

int AC_BaseChar::GetTeamNum()
{
	return TeamNum;
}

