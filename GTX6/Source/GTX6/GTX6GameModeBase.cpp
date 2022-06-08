// Copyright Epic Games, Inc. All Rights Reserved.


#include "GTX6GameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"
#include "GTX6/Extras/MUtils.h"
#include "Kismet/KismetMathLibrary.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"



AGTX6GameModeBase::AGTX6GameModeBase()
{

}

void AGTX6GameModeBase::SpawnAIs()
{
	int distanceToCover = 2000;
	int gapDistance = 500;

	ACharacter* PlayerChar = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);

	if (!PlayerChar)
	{
		MUtils::PM("main player is no spawned");
		return;
	}

	FVector PlayerLoc = PlayerChar->GetActorLocation();
	TArray<FHitResult> out_Results;
	FCollisionShape sphere = FCollisionShape::MakeSphere(distanceToCover);
	bool isHit = GetWorld()->SweepMultiByChannel(out_Results, PlayerLoc, PlayerLoc, FQuat::Identity, ECollisionChannel::ECC_GameTraceChannel2, sphere);
	if (!isHit)
		return;

	for (int i=0;i<out_Results.Num();i++)
	{
		FVector hitLoc = out_Results[i].GetActor()->GetActorLocation();
		if (UKismetMathLibrary::Vector_Distance(PlayerLoc, hitLoc) < distanceToCover - gapDistance)
			continue;

		hitLoc.Z = 300;
		PlayerLoc.Z = 300;
		FHitResult straightHitResult;
		FCollisionQueryParams collisionParam;
		collisionParam.AddIgnoredActor(PlayerChar);
		GetWorld()->LineTraceSingleByChannel(straightHitResult, PlayerLoc, hitLoc, ECollisionChannel::ECC_Camera, collisionParam);
		if (straightHitResult.IsValidBlockingHit())
			continue;

		if (!AICharClass)
		{
			MUtils::PM("you havn't specified the AI in game mode!");
			continue;
		}

		UAIBlueprintHelperLibrary::SpawnAIFromClass(GetWorld(),AICharClass,nullptr,hitLoc);
		MUtils::PM("i Have spawned the ai successful!");



	}

}