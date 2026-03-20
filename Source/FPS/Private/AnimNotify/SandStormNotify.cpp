#include "AnimNotify/SandStormNotify.h"
//-----------------------------------------------------------------------------------------------------------
void USandStormNotify::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	if (!EnemySCIsValid(MeshComp))
		return;

	EnemySC->UseSkillSandStorm();
}
