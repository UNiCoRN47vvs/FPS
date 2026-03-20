#pragma once

#include "CoreMinimal.h"
#include "Enums/CurrencyType.h"
#include "CurrencyStruct.generated.h"
//-----------------------------------------------------------------------------------------------------------
USTRUCT(BlueprintType)
struct FCurrency
{
	GENERATED_BODY()
	FCurrency& operator+=(const FCurrency& OtherCurrency);
	FCurrency& operator*=(const int32 Count);
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Storage Component") float Sulfur = 0.0;
};