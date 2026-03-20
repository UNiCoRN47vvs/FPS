#pragma once

#include "AnimNotify/EnemyAnimNotifyMaster.h"
#include "EnemyIceCageNotify.generated.h"
//-----------------------------------------------------------------------------------------------------------
UCLASS()
class FPS_API UEnemyIceCageNotify : public UEnemyAnimNotifyMaster
{
	GENERATED_BODY()
public:
	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference);

};
//-----------------------------------------------------------------------------------------------------------