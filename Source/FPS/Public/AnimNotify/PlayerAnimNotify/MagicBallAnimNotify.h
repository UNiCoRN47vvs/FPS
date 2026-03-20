#pragma once

#include "AnimNotify/PlayerAnimNotify/PlayerAnimNotifyMaster.h"
#include "MagicBallAnimNotify.generated.h"
//-----------------------------------------------------------------------------------------------------------
UCLASS()
class FPS_API UMagicBallAnimNotify : public UPlayerAnimNotifyMaster
{
	GENERATED_BODY()
public:
	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference);
};
//-----------------------------------------------------------------------------------------------------------