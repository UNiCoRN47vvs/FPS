#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "StatObjects/StatObjectMaster.h"
#include "Enums/StateName.h"
#include "StatData.generated.h"
//-----------------------------------------------------------------------------------------------------------
USTRUCT(BlueprintType)
struct FStatData : public FTableRowBase
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "S_D") EStateName StatName;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "S_D") FGameplayTagContainer GameplayTag;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "S_D") TSubclassOf<UStatObjectMaster> StatObject;
};
//-----------------------------------------------------------------------------------------------------------