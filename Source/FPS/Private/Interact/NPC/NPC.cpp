#include "Interact/NPC/NPC.h"
#include "Config/NPCDA.h"
#include "SubSystem/EventBus.h"
#include "ActorComponents/NPC/NPCStorageComponent.h"
#include "ActorComponents/Quest/QuestGiverComponent.h"
#include "FPS/FPSCharacter.h"
#include "Interact/InteractMaster.h"
//-----------------------------------------------------------------------------------------------------------
ANPC::ANPC()
{
	PrimaryActorTick.bCanEverTick = true;
}
//-----------------------------------------------------------------------------------------------------------
void ANPC::BeginPlay()
{
	Super::BeginPlay();
	InitStore();
}
//-----------------------------------------------------------------------------------------------------------
void ANPC::InitStore()
{
	CHECK_PTR(NPCDA)
	CHECK_WEAK_PTR(GetNPCStorageComponent())

	GetNPCStorageComponent()->InitNPCStorage(NPCDA->ItemsForSaleDataTable);
}
//-----------------------------------------------------------------------------------------------------------
void ANPC::InteractWithActor(ACharacterMaster* playerCharacter)
{
	UEventBus::OnCreateDialogWidget.ExecuteIfBound(GetNPCStorageComponent().Get());
}
//-----------------------------------------------------------------------------------------------------------
FInteractStruct ANPC::GetInteractInfo()
{
	FInteractStruct interactlStruct = {};

	if (!NPCDA)
	{
		ALARM_LOG
		return interactlStruct;
	}

	interactlStruct.InteractButton = NPCDA->InteractButton;
	interactlStruct.ItemName = NPCDA->Name;
	interactlStruct.IteractAction = NPCDA->IteractAction;

	return interactlStruct;
}
//-----------------------------------------------------------------------------------------------------------
TWeakObjectPtr<UNPCStorageComponent> ANPC::GetNPCStorageComponent()
{
	if (!StorageComponent.IsValid())
		StorageComponent = FindComponentByClass<UNPCStorageComponent>();

	return StorageComponent;
}
//-----------------------------------------------------------------------------------------------------------
UQuestGiverComponent* ANPC::GetQuestGiverComponent()
{
	if (!QuestGiverComponent)
		QuestGiverComponent = FindComponentByClass<UQuestGiverComponent>();
	return QuestGiverComponent;
}

