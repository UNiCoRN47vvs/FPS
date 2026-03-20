#include "AnimNotify/PlayerAnimNotify/IceGroundAttackNotify.h"
//-----------------------------------------------------------------------------------------------------------
void UIceGroundAttackNotify::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	if (!PlayerCharacterIsValid(MeshComp) || !PlayerCharacter->GetSkillComponent())
	{
		ALARM_LOG
			return;
	}

	PlayerCharacter->GetSkillComponent()->UseIceGroundAttack();
}
//-----------------------------------------------------------------------------------------------------------