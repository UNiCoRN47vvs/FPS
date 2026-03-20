#pragma once

#include "CoreMinimal.h"
#include "Enums/ItemGrade.h"
#include "ItemDataStruct.generated.h"
//-----------------------------------------------------------------------------------------------------------
USTRUCT(BlueprintType)
struct FItemDataStruct: public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item Inv Struct") EItemGrade ItemGrade;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item Inv Struct") float Chance;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item Inv Struct") int32 DropCountMax = 1;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item Inv Struct") TSoftObjectPtr<UPrimaryDataAsset> DataAsset;
};
