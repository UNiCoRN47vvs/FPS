#pragma once

#include "AnimNotify/EnemyAnimNotifyMaster.h"
#include "FrostveilHandNotify.generated.h"
//-----------------------------------------------------------------------------------------------------------
UCLASS()
class FPS_API UFrostveilHandNotify : public UEnemyAnimNotifyMaster
{
	GENERATED_BODY()
public:
	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference);

};
//-----------------------------------------------------------------------------------------------------------