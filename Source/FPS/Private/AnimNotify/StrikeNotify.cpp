#include "AnimNotify/StrikeNotify.h"
//-----------------------------------------------------------------------------------------------------------
void UStrikeNotify::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	if (!EnemySCIsValid(MeshComp))
	{
		ALARM_LOG
		return;
	}

	EnemySC->UseSkillStrike();
}
