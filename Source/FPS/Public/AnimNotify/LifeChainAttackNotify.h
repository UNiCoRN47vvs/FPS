#pragma once

#include "AnimNotify/EnemyAnimNotifyMaster.h"
#include "LifeChainAttackNotify.generated.h"
//-----------------------------------------------------------------------------------------------------------
UCLASS()
class FPS_API ULifeChainAttackNotify : public UEnemyAnimNotifyMaster
{
	GENERATED_BODY()
public:
	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference);
};
//-----------------------------------------------------------------------------------------------------------