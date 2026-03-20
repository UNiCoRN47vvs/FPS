#pragma once

#include "AnimNotify/EnemyAnimNotifyMaster.h"
#include "EnemyIcecleNotify.generated.h"
//-----------------------------------------------------------------------------------------------------------
UCLASS()
class FPS_API UEnemyIcecleNotify : public UEnemyAnimNotifyMaster
{
	GENERATED_BODY()
public:
	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference);

};
//-----------------------------------------------------------------------------------------------------------