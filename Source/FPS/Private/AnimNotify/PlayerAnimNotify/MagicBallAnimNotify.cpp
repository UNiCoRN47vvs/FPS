#include "AnimNotify/PlayerAnimNotify/MagicBallAnimNotify.h"
//-----------------------------------------------------------------------------------------------------------
void UMagicBallAnimNotify::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	if (!PlayerCharacterIsValid(MeshComp) || !PlayerCharacter->GetSkillComponent())
	{
		ALARM_LOG
			return;
	}

	PlayerCharacter->GetSkillComponent()->UseMagicBall();
}
//-----------------------------------------------------------------------------------------------------------
