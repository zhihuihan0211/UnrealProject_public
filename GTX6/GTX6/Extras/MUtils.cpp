// Fill out your copyright notice in the Description page of Project Settings.


#include "MUtils.h"
#include "DrawDebugHelpers.h"
#include "Perception/AISense_Hearing.h"
#include "Kismet/GameplayStatics.h"
#include "iostream"

MUtils::MUtils()
{
}

MUtils::~MUtils()
{
}

void MUtils::PM(FString data)
{
	std::string dataToString = std::string(TCHAR_TO_UTF8(*data));
	UE_LOG(LogTemp, Warning, TEXT("%s"), *FString(dataToString.c_str()));
}

void MUtils::MS(UWorld* AActor, FVector Center)
{
	DrawDebugSphere(AActor, Center, 50, 32, FColor::Red, true);
}


void MUtils::PlaySoundAtloc(UObject* WorldContextObject, USoundBase* Sound, FVector Location, AActor* Instigator,float MaxRange/* =0 */)
{
	UGameplayStatics::PlaySoundAtLocation(WorldContextObject, Sound, Location);
	UAISense_Hearing::ReportNoiseEvent(WorldContextObject, Location, 1.0f, Instigator, MaxRange);
	
	PM("I am report noise !");
}