#pragma once

#include "Config/SuppliesMasterDA.h"
#include "Enums/CurrencyType.h"
#include "CurrencyMasterDA.generated.h"
//-----------------------------------------------------------------------------------------------------------
UCLASS()
class FPS_API UCurrencyMasterDA : public USuppliesMasterDA
{
	GENERATED_BODY()
public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Currency") ECurrencyType CurrencyType;
};
//-----------------------------------------------------------------------------------------------------------