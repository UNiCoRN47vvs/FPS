#include "AnimNotify/BlizzardNotify.h"
//-----------------------------------------------------------------------------------------------------------
void UBlizzardNotify::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	if (!EnemySCIsValid(MeshComp))
		return;

	EnemySC->UseSkillBlizzard();
}