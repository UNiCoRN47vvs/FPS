#include "AnimNotify/MeleeAttackNotify.h"
//-----------------------------------------------------------------------------------------------------------
void UMeleeAttackNotify::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	if (!EnemySCIsValid(MeshComp))
	{
		ALARM_LOG
		return;
	}

	EnemySC->UseSkillMelee();
}
