#pragma once

#include "AnimNotify/EnemyAnimNotifyMaster.h"
#include "TripleProjectileNotify.generated.h"
//-----------------------------------------------------------------------------------------------------------
class USkillAttackDA;
//-----------------------------------------------------------------------------------------------------------
UCLASS()
class FPS_API UTripleProjectileNotify : public UEnemyAnimNotifyMaster
{
	GENERATED_BODY()

public:
	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference);
};
//-----------------------------------------------------------------------------------------------------------