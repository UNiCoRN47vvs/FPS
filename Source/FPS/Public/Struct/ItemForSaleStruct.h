#pragma once

#include "CoreMinimal.h"
#include "Config/ItemMasterDA.h"
#include "ItemForSaleStruct.generated.h"
//-----------------------------------------------------------------------------------------------------------
USTRUCT(BlueprintType)
struct FItemForSaleStruct : public FTableRowBase
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item For Sale Struct") UItemMasterDA* Item = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item For Sale Struct") int32 Count = 0;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item For Sale Struct") FCurrency CurrencyPrice = {};
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item For Sale Struct") TMap<TSoftObjectPtr<UItemMasterDA>, int32> RecipePrice = {};
};
//-----------------------------------------------------------------------------------------------------------