#pragma once

#include "AnimNotify/EnemyAnimNotifyMaster.h"
#include "AuraNotify.generated.h"
//-----------------------------------------------------------------------------------------------------------
UCLASS()
class FPS_API UAttackAuraNotify : public UEnemyAnimNotifyMaster
{
	GENERATED_BODY()
public:
	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference);
};
//-----------------------------------------------------------------------------------------------------------