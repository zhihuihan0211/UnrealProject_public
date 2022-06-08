// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_Attacking.h"
#include "GTX6/Characters/C_AIChar.h"
#include "AIController.h"

UBTTask_Attacking::UBTTask_Attacking()
{
	NodeName = "Attacking the Player";
}

EBTNodeResult::Type UBTTask_Attacking::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);
	
	//OwnerComp->GetAIOwner()->GetPawn();
	AC_AIChar* AIChar = Cast<AC_AIChar>(OwnerComp.GetAIOwner()->GetPawn());
	AIChar->Scrolling(1);
	AIChar->Attacking();

	return EBTNodeResult::Succeeded;
}