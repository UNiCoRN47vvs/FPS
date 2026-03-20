#pragma once

#include "CoreMinimal.h"
#include "Config/ConsumableSuppliesMasterDA.h"
#include "PotionMasterDA.generated.h"
//-----------------------------------------------------------------------------------------------------------
UCLASS()
class FPS_API UPotionMasterDA : public UConsumableSuppliesMasterDA
{
	GENERATED_BODY()
public:

	virtual bool UseItem(AFPSPlayerController* playerController) override;
};
//-----------------------------------------------------------------------------------------------------------