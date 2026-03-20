#include "AnimNotify/MultiStrikeNotify.h"
//-----------------------------------------------------------------------------------------------------------
void UMultiStrikeNotify::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	if (!EnemySCIsValid(MeshComp))
	{
		ALARM_LOG
		return;
	}

	EnemySC->UseSkillMultiStrike();
}
