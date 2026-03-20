#pragma once

#include "Config/ConsumableSuppliesMasterDA.h"
#include "QuestItemMasterDA.generated.h"
//-----------------------------------------------------------------------------------------------------------
class UQuestInteractTargetMasterDA;
class UWorldRuler;
//-----------------------------------------------------------------------------------------------------------
UCLASS()
class FPS_API UQuestItemMasterDA : public UConsumableSuppliesMasterDA
{
	GENERATED_BODY()
public:
	virtual bool UseItem(AFPSPlayerController* playerController) override;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Q_I_M_DA") UQuestInteractTargetMasterDA* QuestTarget;
protected:
	UPROPERTY() UWorldRuler* WorldRuler;
};
//-----------------------------------------------------------------------------------------------------------