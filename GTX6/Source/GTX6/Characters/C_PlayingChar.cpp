// Fill out your copyright notice in the Description page of Project Settings.


#include "C_PlayingChar.h"
#include "Perception/AIPerceptionStimuliSourceComponent.h"
#include "Perception/AISense_Sight.h"
#include "Perception/AISense_Hearing.h"


AC_PlayingChar::AC_PlayingChar()
{
	AIStumuliSource = CreateDefaultSubobject<UAIPerceptionStimuliSourceComponent>(TEXT("AIStumuliSource"));
	AIStumuliSource->RegisterForSense(TSubclassOf<UAISense_Sight>());

	AIStumuliSource->RegisterForSense(TSubclassOf<UAISense_Hearing>());

	AIStumuliSource->RegisterWithPerceptionSystem();

}