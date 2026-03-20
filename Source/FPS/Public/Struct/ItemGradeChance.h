#pragma once

#include "CoreMinimal.h"
#include "Enums/ItemGrade.h"
#include "ItemGradeChance.generated.h"
//-----------------------------------------------------------------------------------------------------------
USTRUCT(BlueprintType)
struct FItemGradeChance: public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item Inv Struct") EItemGrade ItemGrade;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item Inv Struct") float Chance;
};
