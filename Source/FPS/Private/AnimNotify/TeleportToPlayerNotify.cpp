#include "AnimNotify/TeleportToPlayerNotify.h"
//-----------------------------------------------------------------------------------------------------------
void UTeleportToPlayerNotify::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	if (!EnemySCIsValid(MeshComp))
	{
		ALARM_LOG
			return;
	}

	EnemySC->UseTeleportToPlayer();
}
