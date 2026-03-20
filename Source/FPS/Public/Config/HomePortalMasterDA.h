#pragma once

#include "Config/ConsumableSuppliesMasterDA.h"
#include "HomePortalMasterDA.generated.h"
//-----------------------------------------------------------------------------------------------------------
class AEnterPortal;
//-----------------------------------------------------------------------------------------------------------
UCLASS()
class FPS_API UHomePortalMasterDA : public UConsumableSuppliesMasterDA
{
	GENERATED_BODY()
public:
	virtual bool UseItem(AFPSPlayerController* playerController) override;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Home Portal Master") TSoftClassPtr<AEnterPortal> EnterPortal;

protected:
	UFUNCTION() void HUBLoaded();

	UPROPERTY() AFPSPlayerController* PlayerController;
};

//-----------------------------------------------------------------------------------------------------------