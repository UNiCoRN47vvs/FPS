#pragma once

#include "FPS/FPS.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "ActorComponents/Skill/EnemySC.h"
#include "EnemyAnimNotifyMaster.generated.h"
//-----------------------------------------------------------------------------------------------------------
UCLASS()
class FPS_API UEnemyAnimNotifyMaster : public UAnimNotifyState
{
	GENERATED_BODY()
protected:
	virtual void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference);
	bool EnemySCIsValid(USkeletalMeshComponent* MeshComponent);
	UPROPERTY() UEnemySC* EnemySC;
};
//-----------------------------------------------------------------------------------------------------------