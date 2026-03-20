#pragma once

#include "Config/QuestInteractTargetMasterDA.h"
#include "Struct/InteractStruct.h"
#include "GatheringQuestTargetDA.generated.h"
//-----------------------------------------------------------------------------------------------------------
UCLASS()
class FPS_API UGatheringQuestTargetDA : public UQuestInteractTargetMasterDA
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Q_I_DA") FInteractStruct InteractInfo;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Q_I_DA") USkeletalMesh* SkeletalMesh;

};
//-----------------------------------------------------------------------------------------------------------