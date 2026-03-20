#include "AnimNotify/LifeChainAttackNotify.h"
//-----------------------------------------------------------------------------------------------------------
void ULifeChainAttackNotify::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	if (!EnemySCIsValid(MeshComp))
		return;

	EnemySC->UseSkillLifeChainAttack();
}
