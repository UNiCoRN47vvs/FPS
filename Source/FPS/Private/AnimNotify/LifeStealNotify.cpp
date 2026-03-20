#include "AnimNotify/LifeStealNotify.h"
//-----------------------------------------------------------------------------------------------------------
void ULifeStealNotify::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	if (!EnemySCIsValid(MeshComp))
		return;

	EnemySC->UseSkillLifeSteal();
}
