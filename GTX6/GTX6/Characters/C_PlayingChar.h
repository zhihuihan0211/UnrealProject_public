// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "C_BaseChar.h"
#include "C_PlayingChar.generated.h"

/**
 * 
 */
UCLASS()
class GTX6_API AC_PlayingChar : public AC_BaseChar
{
	GENERATED_BODY()
	
public:
	AC_PlayingChar();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Custom")
		class UAIPerceptionStimuliSourceComponent* AIStumuliSource;

};
