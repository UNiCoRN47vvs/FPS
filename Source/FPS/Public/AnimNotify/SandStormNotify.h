#pragma once

#include "AnimNotify/EnemyAnimNotifyMaster.h"
#include "SandStormNotify.generated.h"
//-----------------------------------------------------------------------------------------------------------
UCLASS()
class FPS_API USandStormNotify : public UEnemyAnimNotifyMaster
{
	GENERATED_BODY()
public:
	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference);
};
//-----------------------------------------------------------------------------------------------------------