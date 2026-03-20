
#pragma once

#include "CoreMinimal.h"
#include "AnimNotify/EnemyAnimNotifyMaster.h"
#include "TeleportToPlayerNotify.generated.h"
//-----------------------------------------------------------------------------------------------------------
UCLASS()
class FPS_API UTeleportToPlayerNotify : public UEnemyAnimNotifyMaster
{
	GENERATED_BODY()

public:
	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference);
};
