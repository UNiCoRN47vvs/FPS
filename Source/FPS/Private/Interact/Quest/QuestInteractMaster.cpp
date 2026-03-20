#include "Interact/Quest/QuestInteractMaster.h"
//-----------------------------------------------------------------------------------------------------------
AQuestInteractMaster::AQuestInteractMaster()
{
	PrimaryActorTick.bCanEverTick = true;
	Tags.Add(FName(TEXT("QuestInteract")));
}
//-----------------------------------------------------------------------------------------------------------
void AQuestInteractMaster::BeginPlay()
{
	Super::BeginPlay();
	InitInteractQuest();
}
//-----------------------------------------------------------------------------------------------------------
void AQuestInteractMaster::InitInteractQuest()
{
}

