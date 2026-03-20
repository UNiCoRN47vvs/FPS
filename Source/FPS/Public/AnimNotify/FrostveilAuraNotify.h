#pragma once

#include "AnimNotify/EnemyAnimNotifyMaster.h"
#include "FrostveilAuraNotify.generated.h"
//-----------------------------------------------------------------------------------------------------------
UCLASS()
class FPS_API UFrostveilAuraNotify : public UEnemyAnimNotifyMaster
{
	GENERATED_BODY()

public:
	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference);

};
//-----------------------------------------------------------------------------------------------------------