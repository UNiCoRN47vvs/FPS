#pragma once

#include "CoreMinimal.h"
#include "Enums/StateName.h"
#include "Enums/ItemGrade.h"
#include "Struct/StatRange.h"
#include "Struct/StatValueStruct.h"
#include "StatStruct.generated.h"
//-----------------------------------------------------------------------------------------------------------
USTRUCT(BlueprintType)
struct FStatStruct
{
	GENERATED_BODY()
	FStatValueStruct FindRandomStatWithRandomValue(EItemGrade itemGrade);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "S_S") TMap<EStateName, FStatRange> StatsMap;
};
//-----------------------------------------------------------------------------------------------------------