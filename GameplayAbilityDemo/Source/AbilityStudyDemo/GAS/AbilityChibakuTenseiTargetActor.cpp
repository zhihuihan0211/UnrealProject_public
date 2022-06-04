// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilityChibakuTenseiTargetActor.h"

#include "Abilities/GameplayAbility.h"

AAbilityChibakuTenseiTargetActor::AAbilityChibakuTenseiTargetActor()
{
	PrimaryActorTick.bCanEverTick=true;
}

void AAbilityChibakuTenseiTargetActor::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	FVector LookLocation;
	
	GetPlayerLookingPoint(LookLocation);
	ConePoint->SetActorLocation(LookLocation);
}


void AAbilityChibakuTenseiTargetActor::StartTargeting(UGameplayAbility* Ability)
{
	Super::StartTargeting(Ability); //OwningAbility = Ability;
	
	MasterPC = Cast<APlayerController>(Ability->GetOwningActorFromActorInfo()->GetInstigatorController());
	SourceActor = Ability->GetOwningActorFromActorInfo();
	// 创建Actor ConePoint用来表示技能的释放位置。
	ConePoint = GetWorld()->SpawnActor<AActor>(ConePointClass,FVector::ZeroVector,FRotator::ZeroRotator);
	
}

void AAbilityChibakuTenseiTargetActor::ConfirmTargetingAndContinue()
{
	FVector ViewLocation;
	GetPlayerLookingPoint(ViewLocation);

	TArray<FOverlapResult> OverlapResults;
	TArray<TWeakObjectPtr<AActor>> OverlapActors;

	FCollisionQueryParams QueryParams;

	QueryParams.bTraceComplex=false;
	QueryParams.bReturnPhysicalMaterial=false;

	if(SourceActor)
		QueryParams.AddIgnoredActor(SourceActor->GetUniqueID());

	bool TryOverlap = GetWorld()->OverlapMultiByObjectType(OverlapResults,ViewLocation,FQuat::Identity,FCollisionObjectQueryParams(ECC_Pawn),
		FCollisionShape::MakeSphere(Radius));

	if(TryOverlap)
	{
		for (FOverlapResult& OverlapResult : OverlapResults)
		{
			APawn* PawnOverlapped = Cast<APawn>(OverlapResult.Actor);
			if(PawnOverlapped)
			{
				OverlapActors.AddUnique(PawnOverlapped);
			}
		}
	}
	
	FVector MeteorSpawnLocation = ConePoint->GetActorLocation();
	MeteorSpawnLocation += ConePoint->GetActorUpVector()*100.0f;

	Meteor= GetWorld()->SpawnActor<AActor>(MeteorClass,MeteorSpawnLocation,ConePoint->GetActorRotation());
	ConePoint->Destroy();

	OverlapActors.Add(Meteor);
	FGameplayAbilityTargetDataHandle TargetDataHandle = StartLocation.MakeTargetDataHandleFromActors(OverlapActors);
	TargetDataReadyDelegate.Broadcast(TargetDataHandle);
}


/*
* GetPlayerLookingPoint用来获取视线与地面的碰撞点：
通过PlayerController→GetPlayerViewPoint(ViewVector, ViewRotation)可以获取角色的视线方向和位置。当然，这里可以通过获取Character的Camera的位置和方向来替代这个函数。
然后通过GetWorld()->LineTraceSingleByChannel从角色视线方向发射一道射线，检测碰撞位置。
发生碰撞后，LookingPoint = HitResult.ImpactPoint就可以得到视线位置。
 */
bool AAbilityChibakuTenseiTargetActor::GetPlayerLookingPoint(FVector& LookingPoint)
{
	FVector ViewVector;
	FRotator ViewRotation;

	if(MasterPC)
	{
		MasterPC->GetPlayerViewPoint(ViewVector,ViewRotation);
	}

	FCollisionQueryParams QueryParams;
	QueryParams.bTraceComplex=false;

	if(SourceActor)
		QueryParams.AddIgnoredActor(SourceActor->GetUniqueID());

	FHitResult HitResult;
	bool TryTrace = GetWorld()->LineTraceSingleByChannel(HitResult,ViewVector,ViewVector+ViewRotation.Vector()*10000.0f,
		ECollisionChannel::ECC_Visibility,QueryParams);

	if(TryTrace)
		LookingPoint = HitResult.ImpactPoint;
	else
		LookingPoint = FVector::ZeroVector;

	return TryTrace;
}
