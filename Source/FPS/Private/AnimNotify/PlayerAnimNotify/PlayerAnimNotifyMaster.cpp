#include "AnimNotify/PlayerAnimNotify/PlayerAnimNotifyMaster.h"
//-----------------------------------------------------------------------------------------------------------
void UPlayerAnimNotifyMaster::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	if (!PlayerCharacterIsValid(MeshComp))
	{
		ALARM_LOG
		return;
	}


}
//-----------------------------------------------------------------------------------------------------------
bool UPlayerAnimNotifyMaster::PlayerCharacterIsValid(USkeletalMeshComponent* MeshComponent)
{
	if (!MeshComponent || !MeshComponent->GetOwner())
	{
		ALARM_LOG
		return false;
	}

	PlayerCharacter = MeshComponent->GetOwner<AFPSCharacter>();
	if (!PlayerCharacter)
	{
		ALARM_LOG
		return false;
	}

	return true;
}
