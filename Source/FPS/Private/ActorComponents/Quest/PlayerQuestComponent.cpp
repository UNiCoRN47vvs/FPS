#include "ActorComponents/Quest/PlayerQuestComponent.h"
#include "Kismet/GameplayStatics.h"
#include "SubSystem/EventBus.h"
#include "FPS/FPSGameMode.h"
#include "Config/QuestMasterDA.h"
#include "Config/EnemyMasterDA.h"
#include "Config/QuestInteractTargetMasterDA.h"
//-----------------------------------------------------------------------------------------------------------
UPlayerQuestComponent::UPlayerQuestComponent()
{
	CurrentQuests = {};
	CompletedQuests = {};
}
//-----------------------------------------------------------------------------------------------------------
//Getters
const TArray<FQuest>& UPlayerQuestComponent::GetCurrentQuests()
{
	return CurrentQuests;
}
const TArray<FQuest>& UPlayerQuestComponent::GetCompletedQuests()
{
	return CompletedQuests;
}
//-----------------------------------------------------------------------------------------------------------
void UPlayerQuestComponent::BeginPlay()
{
	Super::BeginPlay();

	UEventBus::OnUseQuestInteract.BindUObject(this, &UPlayerQuestComponent::ApplyUseQuestInteract);
	UEventBus::OnEnemyDeath.AddUObject(this, &UPlayerQuestComponent::EnemyDeathQuestTrigger);
}
//-----------------------------------------------------------------------------------------------------------
void UPlayerQuestComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	UEventBus::OnUseQuestInteract.Unbind();
	UEventBus::OnEnemyDeath.RemoveAll(this);
}
//-----------------------------------------------------------------------------------------------------------
void UPlayerQuestComponent::SetLoadedData(const TArray<FQuest>& currentQuestsArray, const TArray<FQuest>& completedQuestsArray)
{
	CurrentQuests = currentQuestsArray;
	CompletedQuests = completedQuestsArray;
}
//-----------------------------------------------------------------------------------------------------------
void UPlayerQuestComponent::EnemyDeathQuestTrigger(UEnemyMasterDA* enemyData)
{
	TArray<int32> indexes = {};
	
	FindQuestsByTarget(enemyData, indexes);

	for (const int32& item : indexes)
	{
		AddQuestGoalByIndex(item);
	}
}
//-----------------------------------------------------------------------------------------------------------
void UPlayerQuestComponent::AddNewQuest(const FQuest& quest)
{
	FQuest questStruct = quest;

	CHECK_PTR(quest.QuestMasterDA)

	questStruct.MaxCount = quest.QuestMasterDA->QuestMaxCount;
	CurrentQuests.Add(questStruct);
}
//-----------------------------------------------------------------------------------------------------------
void UPlayerQuestComponent::AddQuestGoalByIndex(const int32 index)
{
	++CurrentQuests[index].CurrentCount;
	OnQuestGoal.ExecuteIfBound(CurrentQuests[index]);
}
//-----------------------------------------------------------------------------------------------------------
bool UPlayerQuestComponent::FindQuestsByTarget(UPrimaryDataAsset* questTargetDA, TArray<int32>& questIndex)
{
	if (!questTargetDA)
		return false;

	TSoftObjectPtr<UPrimaryDataAsset> softQuestTargetDA = questTargetDA;

	for (int32 i = 0; i < CurrentQuests.Num(); ++i)
	{
		if (!CurrentQuests[i].QuestMasterDA)
			continue;

		for (TSoftObjectPtr<UPrimaryDataAsset> LocalItem : CurrentQuests[i].QuestMasterDA->QuestTarget)
		{
			if (LocalItem && LocalItem == softQuestTargetDA && CurrentQuests[i].CurrentCount < CurrentQuests[i].MaxCount)
				questIndex.Add(i);
		}
	}

	if(questIndex.IsEmpty())
		return false;
	else
		return true;
	
}
//-----------------------------------------------------------------------------------------------------------
void UPlayerQuestComponent::QuestComplete(const FQuest& quest)
{
	int32 index = FindQuestIndex(quest);
	if (!CurrentQuests.IsValidIndex(index))
		return;

	CompletedQuests.Add(CurrentQuests[index]);
	CurrentQuests.RemoveAt(index);
}
//-----------------------------------------------------------------------------------------------------------
void UPlayerQuestComponent::TriggerQuestInteract(UQuestInteractTargetMasterDA* questInteractDA)
{
	TArray<int32> indexes = {};

	FindQuestsByTarget(questInteractDA, indexes);

	for (const int32& item : indexes)
	{
		AddQuestGoalByIndex(item);
	}
}
//-----------------------------------------------------------------------------------------------------------
void UPlayerQuestComponent::ApplyUseQuestInteract(UQuestInteractTargetMasterDA* questTargetDA)
{
	bool bIsFindQuestSuccess = false;
	TArray<int32> questIndexes = {};

	bIsFindQuestSuccess = FindQuestsByTarget(questTargetDA, questIndexes);

	if (!bIsFindQuestSuccess)
		return;

	for (int32 item : questIndexes)
	{
		AddQuestGoalByIndex(item);
	}
}
//-----------------------------------------------------------------------------------------------------------
void UPlayerQuestComponent::TESTING_Restore_Completed_Quests()
{
	CurrentQuests.Empty();
	CompletedQuests.Empty();
}
//-----------------------------------------------------------------------------------------------------------
int32 UPlayerQuestComponent::FindQuestIndex(const FQuest& quest)
{
	for (int32 i = 0; i < CurrentQuests.Num(); i++)
	{
		if (CurrentQuests[i].QuestMasterDA == quest.QuestMasterDA)
			return i;
	}

	return 0;
}
