#pragma once

#include "AnimNotify/EnemyAnimNotifyMaster.h"
#include "CircleWaveNotify.generated.h"
//-----------------------------------------------------------------------------------------------------------
UCLASS()
class FPS_API UCircleWaveNotify : public UEnemyAnimNotifyMaster
{
	GENERATED_BODY()
public:
	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference);
};
//-----------------------------------------------------------------------------------------------------------