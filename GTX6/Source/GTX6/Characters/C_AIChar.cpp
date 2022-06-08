// Fill out your copyright notice in the Description page of Project Settings.


#include "C_AIChar.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Perception/AISenseConfig_Hearing.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "Kismet/GameplayStatics.h"
#include <GTX6/Extras/MUtils.h>

AC_AIChar::AC_AIChar()
{
	// sight perception
	AIPerception = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AIPerception"));
	UAISenseConfig_Sight* sightSense = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("sightSense"));

	sightSense->SightRadius = 1000;
	sightSense->LoseSightRadius = 1500;
	sightSense->DetectionByAffiliation.bDetectNeutrals = true;
	AIPerception->ConfigureSense(*sightSense);

	//hear perception
	UAISenseConfig_Hearing* hearSense = CreateDefaultSubobject<UAISenseConfig_Hearing>(TEXT("hearSense"));
	hearSense->HearingRange = 3000;
	hearSense->LoSHearingRange = 3500;
	hearSense->SetMaxAge(0);
	hearSense->DetectionByAffiliation.bDetectNeutrals = true;
	//hearSense->DetectionByAffiliation.bDetectFriendlies = true;

	AIPerception->ConfigureSense(*hearSense);
	AIPerception->SetDominantSense(sightSense->GetSenseImplementation());

	// linking function for perception
	AIPerception->OnTargetPerceptionUpdated.AddDynamic(this, &AC_AIChar::OnTargetPerceptionUpdated);

}

void AC_AIChar::BeginPlay()
{
	Super::BeginPlay();

	AAIController* PawnController = Cast<AAIController>(GetController());

	//PawnController->Run
	PawnController->RunBehaviorTree(BT_AI);

	Setting_NormalMood();

	Cast<AAIController>(GetController())->GetBlackboardComponent()->SetValueAsObject(FName("PlayingChar"), UGameplayStatics::GetPlayerPawn(GetWorld(),0));/*UGameplayStatics::GetplayerPawn(GetWorld(), 0)));*/

}

void AC_AIChar::OnTargetPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus)
{
	if (Stimulus.WasSuccessfullySensed())
	{
		MUtils::PM("i swa him");
	}
	else
	{
		MUtils::PM("he is gone");
	}
}

float AC_AIChar::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser)
{
	Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	Setting_AngrylMood();

	return 0.0f;
}
