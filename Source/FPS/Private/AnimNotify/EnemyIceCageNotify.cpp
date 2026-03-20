#include "AnimNotify/EnemyIceCageNotify.h"
//-----------------------------------------------------------------------------------------------------------
void UEnemyIceCageNotify::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	if (!EnemySCIsValid(MeshComp))
	{
		ALARM_LOG
			return;
	}

	EnemySC->UseSkillIceCage();
}
//-----------------------------------------------------------------------------------------------------------