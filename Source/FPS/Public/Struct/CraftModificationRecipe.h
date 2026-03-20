#pragma once

#include "CoreMinimal.h"
#include "GamePlayTagContainer.h"
#include "Enums/CraftAction.h"
#include "Enums/ItemType.h"
#include "CraftModificationRecipe.generated.h"
//-----------------------------------------------------------------------------------------------------------
class UItemMasterDA;
//-----------------------------------------------------------------------------------------------------------
USTRUCT(BlueprintType)
struct FCraftModificationRecipe : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "C_C_R") EItemType ItemType = {};
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "C_C_R") TMap<TSoftObjectPtr<UItemMasterDA>, int32> RecipeItems = {};
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "C_C_R") ECraftAction CraftAction = {};
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "C_C_R") FGameplayTag StatTag = {};
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "C_C_R") TMap<TSoftObjectPtr<UItemMasterDA>, int32> GiverItems = {};
};
