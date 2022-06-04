// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class EAbilityInputID : uint8
{
	None		UMETA(DisplyName="None"),
	Confirm		UMETA(DisplayName="Confirm"),
	Cancel		UMETA(DisplayName="Cancel"),
	Ability1	UMETA(DisplayName="Ability1"),
};