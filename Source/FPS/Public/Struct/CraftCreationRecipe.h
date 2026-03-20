#pragma once

#include "CoreMinimal.h"
#include "Config/ItemMasterDA.h"
#include "Enums/CraftAction.h"
#include "CraftCreationRecipe.generated.h"
//-----------------------------------------------------------------------------------------------------------
class UItemMasterDA;
//-----------------------------------------------------------------------------------------------------------
USTRUCT(BlueprintType)
struct FCraftCreationRecipe : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "C_C_R") TMap<TSoftObjectPtr<UItemMasterDA>, int32> Items = {};
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "C_C_R") ECraftAction CraftAction = {};
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "C_C_R") TMap<TSoftObjectPtr<UItemMasterDA>, int32> RecipePrice = {};

};
//-----------------------------------------------------------------------------------------------------------