#include "AnimNotify/FrostveilMeleeAttackNotify.h"
//-----------------------------------------------------------------------------------------------------------
void UFrostveilMeleeAttackNotify::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	if (!EnemySCIsValid(MeshComp))
	{
		ALARM_LOG
			return;
	}

	EnemySC->UseSkillFrostveilMelee();
}
//-----------------------------------------------------------------------------------------------------------