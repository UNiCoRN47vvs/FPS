#include "AnimNotify/EnemyProjectileSpawnerNotify.h"
//-----------------------------------------------------------------------------------------------------------
void UEnemyProjectileSpawnerNotify::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	if (!EnemySCIsValid(MeshComp))
	{
		ALARM_LOG
			return;
	}

	EnemySC->UseSkillProjectileSpawner();
}
