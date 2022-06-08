// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "MyDataAssetTest.generated.h"

/**
 * 
 */
UCLASS()
class GTX6_API UMyDataAssetTest : public UDataAsset
{
	GENERATED_BODY()

};

UCLASS()
class UMyPrimaryDataAsset : public UPrimaryDataAsset
{
	GENERATED_BODY()
public:
	UFUNCTION()
	void setAtt()
	{

	}
};



