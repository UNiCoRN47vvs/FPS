#include "ActorComponents/Quest/QuestGiverComponent.h"
#include "AssetRegistry/AssetRegistryModule.h"
#include "AssetRegistry/IAssetRegistry.h"
#include "Engine/StreamableManager.h"
#include "Engine/AssetManager.h"
#include "ActorComponents/Quest/PlayerQuestComponent.h"
#include "Config/QuestsDA.h"
#include "Config/QuestMasterDA.h"
//-----------------------------------------------------------------------------------------------------------
UQuestGiverComponent::UQuestGiverComponent()
{
}
//-----------------------------------------------------------------------------------------------------------
void UQuestGiverComponent::BeginPlay()
{
	Super::BeginPlay();

	// Проверка на загружаемость при сборке (ну почти)
	//TArray<FPrimaryAssetId> outAssetList = {};
	//UAssetManager::Get().GetPrimaryAssetIdList(FPrimaryAssetType("QuestMasterDA"), outAssetList);

}
//-----------------------------------------------------------------------------------------------------------
void UQuestGiverComponent::BeginDestroy()
{
	Super::BeginDestroy();
}
//-----------------------------------------------------------------------------------------------------------
void UQuestGiverComponent::LoadAllQuestDataAssetsFromPath()
{
	/*UQuestMasterDA* loadedAsset = nullptr;
	FAssetRegistryModule& assetRegistryModule = FModuleManager::LoadModuleChecked<FAssetRegistryModule>("AssetRegistry");
	IAssetRegistry& assetRegistry = assetRegistryModule.Get();
	FARFilter filter = {};
	TArray<FAssetData> assetDataList = {};

	filter.PackagePaths.Add(*FolderPath);
	filter.ClassPaths.Add(UQuestMasterDA::StaticClass()->GetClassPathName());
	filter.bRecursivePaths = true;
	filter.bRecursiveClasses = true;

	assetRegistry.GetAssets(filter, assetDataList);

	for (const FAssetData& assetData : assetDataList)
	{
		loadedAsset = Cast<UQuestMasterDA>(assetData.GetAsset());
		if (loadedAsset)
			ArrayQuestsDA.Add(loadedAsset);
	}*/
}
//-----------------------------------------------------------------------------------------------------------
TArray<FQuest> UQuestGiverComponent::GetAllAvailableQuests(UPlayerQuestComponent* playerQuestComp)
{
	if (!IsValid(playerQuestComp))
	{
		ALARM_LOG
		return TArray<FQuest>();
	}

	bool bQuestCompleted = false;
	bool bQuestRequirement = false;
	int32 questMaxCount = QuestMaxCount;
	UQuestMasterDA* loadedAsset = nullptr;
	FAssetRegistryModule& assetRegistryModule = FModuleManager::LoadModuleChecked<FAssetRegistryModule>("AssetRegistry");
	IAssetRegistry& assetRegistry = assetRegistryModule.Get();
	const TArray<FQuest>& playerCompletedQuests = playerQuestComp->GetCompletedQuests();
	const TArray<FQuest>& playerCurrentQuests = playerQuestComp->GetCurrentQuests();
	FARFilter filter = {};
	FQuest questStruct = {};
	TArray<FQuest> questGiverQuests = {};
	TArray<FAssetData> assetDataList = {};
	TArray<UQuestMasterDA*> qualifiedDA = {};

	filter.PackagePaths.Add(*FolderPath);
	filter.ClassPaths.Add(UQuestMasterDA::StaticClass()->GetClassPathName());
	filter.bRecursivePaths = true;
	filter.bRecursiveClasses = true;

	assetRegistry.GetAssets(filter, assetDataList);

	for (const FAssetData& assetData : assetDataList)
	{
		loadedAsset = Cast<UQuestMasterDA>(assetData.GetAsset());
		if (!loadedAsset)
			continue;

		qualifiedDA.Add(loadedAsset);
	}

	for (int32 i = 0; i < qualifiedDA.Num(); i++)
	{
		for (int32 j = 0; j < qualifiedDA.Num(); j++)
		{
			if (qualifiedDA[i]->UnicQuestLevel < qualifiedDA[j]->UnicQuestLevel)
				qualifiedDA.Swap(i, j);
		}
	}

	for (UQuestMasterDA* item : qualifiedDA)
	{
		if (questMaxCount <= 0)
			break;

		for (int32 i = 0; i < playerCompletedQuests.Num(); i++)
		{
			if (item == playerCompletedQuests[i].QuestMasterDA)
			{
				bQuestCompleted = true;
				break;
			}

			if (playerCompletedQuests[i].QuestMasterDA == item->QuestRequirement)
				bQuestRequirement = true;
		}

		if (bQuestCompleted)
		{
			bQuestCompleted = false;
			continue;
		}

		if (item->QuestRequirement && !bQuestRequirement)
			continue;
		
		bQuestRequirement = false;

		questStruct.QuestMasterDA = item;

		for (const FQuest& subItem : playerCurrentQuests)
		{
			if (item == subItem.QuestMasterDA)
			{
				questStruct = subItem;
				break;
			}
		}

		questGiverQuests.Add(questStruct);
		--questMaxCount;

		questStruct.CurrentCount = 0;
		questStruct.MaxCount = 0;
		questStruct.QuestMasterDA = nullptr;
	}

	return questGiverQuests;
}
