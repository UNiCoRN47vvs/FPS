#pragma once

#include "CoreMinimal.h"
#include "Enums/StateName.h"
#include "StatValueStruct.generated.h"
//-----------------------------------------------------------------------------------------------------------
USTRUCT(BlueprintType)
struct FStatValueStruct
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "S_V_S") TMap<EStateName, float> StatsValue;
};
