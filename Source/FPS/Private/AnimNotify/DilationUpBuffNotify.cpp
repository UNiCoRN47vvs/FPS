#include "AnimNotify/DilationUpBuffNotify.h"
//-----------------------------------------------------------------------------------------------------------
void UDilationUpBuffNotify::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	if (!EnemySCIsValid(MeshComp))
	{
		ALARM_LOG
			return;
	}

	EnemySC->UseSkillDilationUpBuff();
}
