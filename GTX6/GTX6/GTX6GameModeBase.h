// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Characters/C_AIChar.h"

#include "GTX6GameModeBase.generated.h"
/**
 * 
 */
UCLASS()
class GTX6_API AGTX6GameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	AGTX6GameModeBase();


	//this function just Spawn AIS, just remember to add class i defaults;
	UFUNCTION(BlueprintCallable)
	void SpawnAIs();

	UPROPERTY(BlueprintReadWrite,EditAnywhere)
		TSubclassOf<AC_AIChar> AICharClass;
};
