#include "AnimNotify/BubbleNotify.h"
//-----------------------------------------------------------------------------------------------------------
void UEnemyDefenseNotify::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	if (!EnemySCIsValid(MeshComp))
		return;

	EnemySC->UseSkillBubble();
}
