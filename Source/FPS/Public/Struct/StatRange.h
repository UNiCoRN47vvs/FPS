#pragma once

#include "CoreMinimal.h"
#include "StatRange.generated.h"
//-----------------------------------------------------------------------------------------------------------
USTRUCT(BlueprintType)
struct FStatRange
{
	GENERATED_BODY()
	float GetValueFromRange();
	float GetMiddleValue();
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "D_R") float ValueMin = 0.0;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "D_R") float ValueMax = 0.0;
};
