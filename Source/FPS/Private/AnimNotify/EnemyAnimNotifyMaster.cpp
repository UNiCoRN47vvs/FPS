#include "AnimNotify/EnemyAnimNotifyMaster.h"
//-----------------------------------------------------------------------------------------------------------
void UEnemyAnimNotifyMaster::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	if (!EnemySCIsValid(MeshComp))
	{
		ALARM_LOG
		return;
	}

	EnemySC->AttackEnded();
}
//-----------------------------------------------------------------------------------------------------------
bool UEnemyAnimNotifyMaster::EnemySCIsValid(USkeletalMeshComponent* MeshComponent)
{
	if (!MeshComponent || !MeshComponent->GetOwner())
	{
		ALARM_LOG
		return false;
	}

	EnemySC = MeshComponent->GetOwner()->FindComponentByClass<UEnemySC>();
	if (!EnemySC)
	{
		ALARM_LOG
		return false;
	}
	return true;
}
//-----------------------------------------------------------------------------------------------------------
