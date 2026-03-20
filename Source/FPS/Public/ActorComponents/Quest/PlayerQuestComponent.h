#pragma once

#include "ActorComponents/Quest/QuestMasterComponent.h"
#include "Struct/QuestStruct.h"
#include "PlayerQuestComponent.generated.h"
//-----------------------------------------------------------------------------------------------------------
class UEnemyMasterDA;
class UQuestInteractTargetMasterDA;
//-----------------------------------------------------------------------------------------------------------
UCLASS()
class FPS_API UPlayerQuestComponent : public UQuestMasterComponent
{
	GENERATED_BODY()
public:
	UPlayerQuestComponent();
	//**************************
	//Getters
	const TArray<FQuest>& GetCurrentQuests();
	const TArray<FQuest>& GetCompletedQuests();
	//**************************
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	void SetLoadedData(const TArray<FQuest>& currentQuestsArray, const TArray<FQuest>& completedQuestsArray);
	void AddNewQuest(const FQuest& quest);
	void AddQuestGoalByIndex(const int32 index);
	bool FindQuestsByTarget(UPrimaryDataAsset* questTargetDA, TArray<int32>& questIndex);
	void QuestComplete(const FQuest& quest);
	void TriggerQuestInteract(UQuestInteractTargetMasterDA* questInteractDA);

	TDelegate<void(FQuest)> OnQuestGoal;
protected:
	UFUNCTION(BlueprintCallable) void TESTING_Restore_Completed_Quests();
	int32 FindQuestIndex(const FQuest& QuestStruct);
	UFUNCTION() void EnemyDeathQuestTrigger(UEnemyMasterDA* enemyData);
	void ApplyUseQuestInteract(UQuestInteractTargetMasterDA* questTargetDA);
	UPROPERTY() TArray<FQuest> CurrentQuests;
	UPROPERTY() TArray<FQuest> CompletedQuests;	
};
//-----------------------------------------------------------------------------------------------------------