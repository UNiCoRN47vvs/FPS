#pragma once

#include "Config/SuppliesMasterDA.h"
#include "RuneMasterDA.generated.h"
//-----------------------------------------------------------------------------------------------------------
UCLASS()
class FPS_API URuneMasterDA : public USuppliesMasterDA
{
	GENERATED_BODY()
public:
	virtual void ApplyRuneData() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "R_M_DA") EItemType TargetItemType = {};
};
//-----------------------------------------------------------------------------------------------------------