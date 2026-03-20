#pragma once

#include "AnimNotify/EnemyAnimNotifyMaster.h"
#include "DilationUpBuffNotify.generated.h"
//-----------------------------------------------------------------------------------------------------------
UCLASS()
class FPS_API UDilationUpBuffNotify : public UEnemyAnimNotifyMaster
{
	GENERATED_BODY()

public:
	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference);
};
//-----------------------------------------------------------------------------------------------------------