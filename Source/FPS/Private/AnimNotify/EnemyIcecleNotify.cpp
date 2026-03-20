#include "AnimNotify/EnemyIcecleNotify.h"
//-----------------------------------------------------------------------------------------------------------
void UEnemyIcecleNotify::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	if (!EnemySCIsValid(MeshComp))
	{
		ALARM_LOG
			return;
	}

	EnemySC->UseSkillIcecleProjectile();
}
//-----------------------------------------------------------------------------------------------------------