// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_Attacking.generated.h"

/**
 * 
 */
UCLASS()
class GTX6_API UBTTask_Attacking : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UBTTask_Attacking();

protected:

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	
};
