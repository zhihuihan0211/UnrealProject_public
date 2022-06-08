// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_ChooseCheckPoint.generated.h"

/**
 * 
 */
UCLASS()
class GTX6_API UBTTask_ChooseCheckPoint : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

	UBTTask_ChooseCheckPoint();

protected:

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

};
