#pragma once

#include "AnimNotify/EnemyAnimNotifyMaster.h"
#include "HomingProjectileNotify.generated.h"
//-----------------------------------------------------------------------------------------------------------
UCLASS()
class FPS_API UHomingProjectileNotify : public UEnemyAnimNotifyMaster
{
	GENERATED_BODY()
public:
	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference);
	
};
//-----------------------------------------------------------------------------------------------------------