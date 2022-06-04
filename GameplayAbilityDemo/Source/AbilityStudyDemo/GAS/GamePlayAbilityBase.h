#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "AbilityStudyDemo/AbilityStudyDemo.h"
#include "GamePlayAbilityBase.generated.h"

UCLASS()
class ABILITYSTUDYDEMO_API UGamePlayAbilityBase : public UGameplayAbility
{
	GENERATED_BODY()

		
public:

	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="AbilityBase")
	EAbilityInputID AbilityInputID=EAbilityInputID::None;
	
};
