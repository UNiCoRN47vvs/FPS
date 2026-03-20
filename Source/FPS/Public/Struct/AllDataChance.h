#pragma once

#include "CoreMinimal.h"
#include "Enums/ItemGrade.h"
#include "AllDataChance.generated.h"
//-----------------------------------------------------------------------------------------------------------
USTRUCT(BlueprintType)
struct FAllDataChance : public FTableRowBase
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "All Data Chance") EItemGrade Grade = EItemGrade::White;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "All Data Chance") UDataTable* DataTable = nullptr;
};
//-----------------------------------------------------------------------------------------------------------