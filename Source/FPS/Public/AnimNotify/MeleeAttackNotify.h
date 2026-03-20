#pragma once

#include "AnimNotify/EnemyAnimNotifyMaster.h"
#include "MeleeAttackNotify.generated.h"
//-----------------------------------------------------------------------------------------------------------
UCLASS()
class FPS_API UMeleeAttackNotify : public UEnemyAnimNotifyMaster
{
	GENERATED_BODY()
	
public:
	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference);
};
//-----------------------------------------------------------------------------------------------------------