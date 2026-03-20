#pragma once

#include "FPS/FPS.h"
#include "Config/ItemMasterDA.h"
#include "Enums/ItemGrade.h"
#include "Struct/StatValueStruct.h"
#include "ItemInvStruct.generated.h"
//-----------------------------------------------------------------------------------------------------------
USTRUCT(BlueprintType)
struct FItemInvStruct
{
	GENERATED_BODY()
	TMap<EStateName, float> GetItemStatFromLevel();
	FStatRange GetItemDamageFromLevel();
	TMap<FString, FText> GetItemInfo();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "I_I_S") bool bOccupied = false;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "I_I_S") int32 ItemCount = 0;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "I_I_S") int32 ItemLevel = 0;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "I_I_S") UItemMasterDA* ItemDA = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "I_I_S") FStatValueStruct StatValue = {};

protected:
	UPROPERTY() UItemMasterDA* NextUpgradeDA;
};
//-----------------------------------------------------------------------------------------------------------