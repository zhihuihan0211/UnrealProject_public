// Fill out your copyright notice in the Description page of Project Settings.


#include "MyBTTaskNode.h"

#include "NavigationSystem.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"


UMyBTTaskNode::UMyBTTaskNode()
{
	NodeName = "Choose Random Location";
}

EBTNodeResult::Type UMyBTTaskNode::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	FVector PawnLocation = OwnerComp.GetOwner()->GetActorLocation();

	FNavLocation nav_location;
	
	UNavigationSystemV1::GetCurrent(GetWorld())->GetRandomReachablePointInRadius( PawnLocation, 1000, nav_location);

	OwnerComp.GetBlackboardComponent()->SetValueAsVector(FName("targetLoc"), nav_location);

	//OwnerComp.GetAIOwner()->GetBlackboardComponent()->SetValueAsVector()
	return EBTNodeResult::Succeeded;

}