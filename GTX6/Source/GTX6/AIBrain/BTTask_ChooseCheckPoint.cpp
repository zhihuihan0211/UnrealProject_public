// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_ChooseCheckPoint.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include <Runtime/Engine/Classes/Kismet/KismetMathLibrary.h>

UBTTask_ChooseCheckPoint::UBTTask_ChooseCheckPoint()
{

	NodeName = "Choosing Check Point";
}

EBTNodeResult::Type UBTTask_ChooseCheckPoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	FVector pawnLocation = OwnerComp.GetAIOwner()->GetPawn()->GetActorLocation();// 
	FCollisionShape sphere = FCollisionShape::MakeSphere(200);
	TArray<AActor*> ignoreActor;
	TArray<FHitResult> out_Results;
	bool isHit = GetWorld()->SweepMultiByChannel(out_Results, pawnLocation, pawnLocation, FQuat::Identity,ECollisionChannel::ECC_GameTraceChannel2, sphere);

	if (isHit)
	{
		FVector visitedLocation = OwnerComp.GetBlackboardComponent()->GetValueAsVector(GetSelectedBlackboardKey());
		bool isFound = false;

		while (out_Results.Num()>0)
		{
			int ChooseIndex = UKismetMathLibrary::RandomIntegerInRange(0, out_Results.Num() - 1);
			FVector chooseLocation = out_Results[ChooseIndex].GetActor()->GetActorLocation();
			// distance between pawn  and choose checkpoint
			int dis_PawnCheckPoint = UKismetMathLibrary::Vector_Distance(pawnLocation, chooseLocation);

			//distance between selected checkpoint and previous location
			int dis_CheckPointVisited = UKismetMathLibrary::Vector_Distance(visitedLocation, chooseLocation);

			if (dis_PawnCheckPoint > 100 && dis_CheckPointVisited > 300)
			{
				isFound = true;
				OwnerComp.GetBlackboardComponent()->SetValueAsVector(FName("targetLoc"), chooseLocation);
				OwnerComp.GetBlackboardComponent()->SetValueAsVector(FName("VisitedLoc"), pawnLocation);
				break;
			}
			if (!isFound)
			{
				OwnerComp.GetBlackboardComponent()->SetValueAsVector(GetSelectedBlackboardKey(), FVector::ZeroVector);
				
				return EBTNodeResult::Failed;
			}
		}
 	}

	//VisitedLoc
	return EBTNodeResult::Succeeded;
}