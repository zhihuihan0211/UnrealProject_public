// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class GTX6_API MUtils
{
public:
	MUtils();
	~MUtils();

	static void PM(FString data);

	static void MS(UWorld* AActor, FVector Center);

	static void PlaySoundAtloc(UObject* WorldContextObject, USoundBase* Sound, FVector Location, AActor* Instigator,float MaxRange=0);
};
