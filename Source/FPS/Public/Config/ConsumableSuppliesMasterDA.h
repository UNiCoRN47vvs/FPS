#pragma once

#include "Config/SuppliesMasterDA.h"
#include "Enums/StateName.h"
#include "ConsumableSuppliesMasterDA.generated.h"
//-----------------------------------------------------------------------------------------------------------
UCLASS()
class FPS_API UConsumableSuppliesMasterDA : public USuppliesMasterDA
{
	GENERATED_BODY()
public:
	virtual bool UseItem(AFPSPlayerController* playerController) override;
	virtual TMap<FString, FText> GetItemInfo() override;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Consumable Supplies") TMap<EStateName, float> StatModifier;
	
};
