// Fill out your copyright notice in the Description page of Project Settings.


#include "UAbilityShinraTenseiTargetActor.h"

#include "Abilities/GameplayAbility.h"

AUAbilityShinraTenseiTargetActor::AUAbilityShinraTenseiTargetActor()
{
	//Radius=1000;
}

void AUAbilityShinraTenseiTargetActor::StartTargeting(UGameplayAbility* Ability)
{
	Super::StartTargeting(Ability);
	MasterPC = Cast<APlayerController>(Ability->GetOwningActorFromActorInfo()->GetInstigatorController());
	SourceActor = Ability->GetOwningActorFromActorInfo();
	
	
}

void AUAbilityShinraTenseiTargetActor::ConfirmTargeting()
{
	// Super::ConfirmTargeting();
	FVector AbilityStartLocation = FVector::ZeroVector;
	TArray<FOverlapResult> OverlapResults;
	TArray<TWeakObjectPtr<AActor>> OverlapActors;

	FCollisionQueryParams QueryParams;
	QueryParams.bTraceComplex = false;
	QueryParams.bReturnPhysicalMaterial=false;

	if(SourceActor)
	{
		QueryParams.AddIgnoredActor(SourceActor->GetUniqueID());
		AbilityStartLocation = SourceActor->GetActorLocation();
	}

	//UE_LOG(LogTemp,Warning,TEXT("AbilityStartLocation = %s"),string(AbilityStartLocation));
	
	//构建球形碰撞体，进行碰撞检测
	bool TryOverlap = GetWorld()->OverlapMultiByObjectType(OverlapResults,AbilityStartLocation,FQuat::Identity,
		FCollisionObjectQueryParams(ECC_Pawn),FCollisionShape::MakeSphere(Radius),QueryParams);
	
	if(TryOverlap)
	{
		for(const FOverlapResult& Result:OverlapResults)
		{
			APawn* OverlappedPawn = Cast<APawn>(Result.Actor);
			if(IsValid(OverlappedPawn))
			{
				OverlapActors.AddUnique(OverlappedPawn);
			}
		}
	}

	//如果OverlapActors存在数据，将数据通过delegate广播
	if(OverlapActors.Num()>0)
	{
		const FGameplayAbilityTargetDataHandle TargetData = StartLocation.MakeTargetDataHandleFromActors(OverlapActors);
		TargetDataReadyDelegate.Broadcast(TargetData);
	}
	
}
