#include "Interact/Quest/GatheringQuestInteract.h"
#include "Character/CharacterMaster.h"
#include "Config/GatheringQuestTargetDA.h"
//-----------------------------------------------------------------------------------------------------------
AGatheringQuestInteract::AGatheringQuestInteract()
{
	SkeletalMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(FName(TEXT("Static Mesh Component")));
}
//-----------------------------------------------------------------------------------------------------------
void AGatheringQuestInteract::InitInteractQuest()
{
	if (FMath::RandRange(0, 2) != 0)
	{
		Destroy();
		return;
	}

	UGatheringQuestTargetDA* gatheringQuestInteractDA = Cast<UGatheringQuestTargetDA>(QuestInteractDA);
	CHECK_PTR(gatheringQuestInteractDA)

	PTR(SkeletalMeshComponent)->SetSkeletalMesh(gatheringQuestInteractDA->SkeletalMesh);
}
//-----------------------------------------------------------------------------------------------------------
void AGatheringQuestInteract::InteractWithActor(ACharacterMaster* playerCharacter)
{
	PTR(playerCharacter)->TriggerQuestInteract(QuestInteractDA);
	Destroy();
}
//-----------------------------------------------------------------------------------------------------------
FInteractStruct AGatheringQuestInteract::GetInteractInfo()
{
	UGatheringQuestTargetDA* gatheringQuestInteractDA = Cast<UGatheringQuestTargetDA>(QuestInteractDA);
	if (!gatheringQuestInteractDA)
	{
		ALARM_LOG
		return FInteractStruct{};
	}

	return gatheringQuestInteractDA->InteractInfo;
}
//-----------------------------------------------------------------------------------------------------------