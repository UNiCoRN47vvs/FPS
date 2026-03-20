#pragma once

#include "CoreMinimal.h"
#include "Struct/ItemTypeChance.h"
#include "ItemTypeData.generated.h"
//-----------------------------------------------------------------------------------------------------------
USTRUCT(BlueprintType)
struct FItemTypeData: public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item Inv Struct") ETypeChance ItemType;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item Inv Struct") UDataTable* DataTable;
};
