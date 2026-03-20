#pragma once

#include "AnimNotify/EnemyAnimNotifyMaster.h"
#include "BlizzardNotify.generated.h"
//-----------------------------------------------------------------------------------------------------------
UCLASS()
class FPS_API UBlizzardNotify : public UEnemyAnimNotifyMaster
{
	GENERATED_BODY()
public:
	void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference);
};
//-----------------------------------------------------------------------------------------------------------