#include "AnimNotify/HomingProjectileNotify.h"
//-----------------------------------------------------------------------------------------------------------
void UHomingProjectileNotify::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	if (!EnemySCIsValid(MeshComp))
	{
		ALARM_LOG
			return;
	}

	EnemySC->UseSkillHomingProjectile();
}
//-----------------------------------------------------------------------------------------------------------
