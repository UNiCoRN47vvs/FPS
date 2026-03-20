#pragma once

#include "Config/SuppliesMasterDA.h"
#include "Struct/StatValueStruct.h"
#include "ArmorMasterDA.generated.h"
//-----------------------------------------------------------------------------------------------------------
UCLASS()
class FPS_API UArmorMasterDA : public USuppliesMasterDA
{
	GENERATED_BODY()
public:
	/*virtual TMap<FString, FText> GetItemInfo() override;*/
	virtual TMap<EStateName, float> GetItemStat() override;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "A_M_DA") FStatValueStruct ArmorStat = {};

};
//-----------------------------------------------------------------------------------------------------------