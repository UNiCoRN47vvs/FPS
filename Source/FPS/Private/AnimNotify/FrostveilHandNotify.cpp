#include "AnimNotify/FrostveilHandNotify.h"
//-----------------------------------------------------------------------------------------------------------
void UFrostveilHandNotify::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	if (!EnemySCIsValid(MeshComp))
	{
		ALARM_LOG
		return;
	}

	EnemySC->UseSkillFrostveilHand();
}
//-----------------------------------------------------------------------------------------------------------