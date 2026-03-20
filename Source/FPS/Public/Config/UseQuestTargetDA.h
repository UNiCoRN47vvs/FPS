#pragma once

#include "Config/QuestInteractTargetMasterDA.h"
#include "UseQuestTargetDA.generated.h"
//-----------------------------------------------------------------------------------------------------------
class UItemMasterDA;
//-----------------------------------------------------------------------------------------------------------
UCLASS()
class FPS_API UUseQuestTargetDA : public UQuestInteractTargetMasterDA
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "U_Q_I_DA") UItemMasterDA* ItemDA;
};
//-----------------------------------------------------------------------------------------------------------