#include "FirstPerson/FPSGameInstance.h"
#include "Engine/AssetManager.h"
#include "Engine/StreamableManager.h"
#include "GameFramework/GameUserSettings.h"
#include "Kismet/GameplayStatics.h"
#include "SubSystem/EventBus.h"
#include "SubSystem/StatDataSubsystem.h"
#include "Sound/SoundClass.h"
#include "Save/MasterSave.h"
//-----------------------------------------------------------------------------------------------------------
TDelegate<UInputMappingContext* ()> UFPSGameInstance::OnGetInputMapingContext;
//-----------------------------------------------------------------------------------------------------------
UFPSGameInstance::UFPSGameInstance()
{
	SaveName = FString(TEXT("GGWP"));
}
//-----------------------------------------------------------------------------------------------------------
//Getter
const FString& UFPSGameInstance::GetSaveName()
{
	if (bIsDebug)
		return DebugSaveName;

	return SaveName;
}
//-----------------------------------------------------------------------------------------------------------
TMap<FName, bool>& UFPSGameInstance::GetSaveInfoMap()
{
	UMasterSave* masterSave = Cast<UMasterSave>(UGameplayStatics::LoadGameFromSlot(FString(TEXT("MasterSave")), 0));

	if (!masterSave || !masterSave->MasterSave.Contains(SaveName))
		return TempMap;
	
	return masterSave->MasterSave.Find(SaveName)->InfoMap;
}
//-----------------------------------------------------------------------------------------------------------
void UFPSGameInstance::SetSaveName(const FString& name)
{
	SaveName = name;
}
//-----------------------------------------------------------------------------------------------------------
void UFPSGameInstance::Init()
{
	Super::Init();

	OnGetInputMapingContext.BindLambda([this]() { return InputMappingContext; });
	UEventBus::OnGetSaveInfoMap.BindUObject(this, &UFPSGameInstance::GetSaveInfoMap);

	bool bIsSaveGameExist = false;
	UMasterSave* masterSave = nullptr;

	PTR(UGameUserSettings::GetGameUserSettings())->LoadSettings();
	UGameUserSettings::GetGameUserSettings()->ApplySettings(false);

	if (!UGameplayStatics::DoesSaveGameExist(FString(TEXT("MasterSave")), 0))
		masterSave = Cast<UMasterSave>(UGameplayStatics::CreateSaveGameObject(UMasterSave::StaticClass()));
	else
	{
		masterSave = Cast<UMasterSave>(UGameplayStatics::LoadGameFromSlot(FString(TEXT("MasterSave")), 0));
		bIsSaveGameExist = true;
	}

	CHECK_PTR(masterSave)

	if (!bIsSaveGameExist)
	{
		masterSave->SettingsSave.bIsShowFPS = false;
		masterSave->SettingsSave.AntiAliasingMethod = 0;
		masterSave->SettingsSave.MSAACount = 1;
		masterSave->SettingsSave.SoundMasterValue = 0.5f;
		masterSave->SettingsSave.SoundEffectValue = 0.5f;
		masterSave->SettingsSave.SoundMusicValue = 0.5f;
	}

	GEngine->Exec(GetWorld(), *(FString(TEXT("r.AntiAliasingMethod ")) + FString::FromInt(masterSave->SettingsSave.AntiAliasingMethod)));
	GEngine->Exec(GetWorld(), *(FString(TEXT("r.MSAACount ")) + FString::FromInt(masterSave->SettingsSave.MSAACount)));
	
	SoundMaster->Properties.Volume = masterSave->SettingsSave.SoundMasterValue;
	SoundEffect->Properties.Volume = masterSave->SettingsSave.SoundEffectValue;
	SoundMusic->Properties.Volume = masterSave->SettingsSave.SoundMusicValue;

	UGameplayStatics::SaveGameToSlot(masterSave, FString(TEXT("MasterSave")), 0);

	InitStat<FStatData>(UStatDataSubsystem::StatArray, StatDataDT);
	InitStat<FStatGradeData>(UStatDataSubsystem::StatGradeArray, StatGradeDataDT);

	FTimerHandle sortHandle1 = {};

	GetWorld()->GetTimerManager().SetTimer(sortHandle1, [this]() 
		{
			CraftCreationSort();
			CraftModificationSort();
		}, 0.1f, false);
	
}
//-----------------------------------------------------------------------------------------------------------
template<typename StructClass>
inline void UFPSGameInstance::InitStat(TArray<StructClass>& statArray, TSoftObjectPtr<UDataTable> dataTable)
{
	UDataTable* statDataTable = nullptr;
	FString contextString = {};
	StructClass statData = {};
	TArray<StructClass*> allRowsDT = {};
	TArray<StructClass> stat = {};

	if (dataTable.Get())
		statDataTable = dataTable.Get();
	else
		statDataTable = dataTable.LoadSynchronous();

	CHECK_PTR(statDataTable)

	statDataTable->GetAllRows(contextString, allRowsDT);

	stat.Init(statData, allRowsDT.Num());

	for (const StructClass* item : allRowsDT)
	{
		stat[static_cast<int32>(item->StatName)] = *item;
	}

	statArray = stat;
}
//-----------------------------------------------------------------------------------------------------------
void UFPSGameInstance::CraftCreationSort()
{
	if (!CraftCreationDT.Get())
	{
		UAssetManager::GetStreamableManager().RequestAsyncLoad(CraftCreationDT.ToSoftObjectPath(), [this]()
			{
				AsyncTask(ENamedThreads::GameThread, [this]()
					{
						CraftCreationSort();
					});
			});

		return;
	}

	FString itemsPathNames = {};
	FString contextString = {};
	TArray<FCraftCreationRecipe*> creationRecipeArray = {};
	TArray<FString> itemsPathArray = {};

	CraftCreationDT.Get()->GetAllRows(contextString, creationRecipeArray);

	for (const FCraftCreationRecipe* item : creationRecipeArray)
	{
		for (const auto& subItem : item->RecipePrice)
		{
			itemsPathArray.Add(subItem.Key.ToSoftObjectPath().ToString());
		}

		itemsPathArray.Sort();

		for (const FString& subItem : itemsPathArray)
		{
			itemsPathNames += subItem;
		}

		UStatDataSubsystem::CreationRecipeMap.Add(FName(*itemsPathNames), *item);
		
		itemsPathArray.Empty();
		itemsPathNames.Empty();
	}

	/*AsyncTask(ENamedThreads::AnyBackgroundThreadNormalTask, [this]()
		{});*/
}
//-----------------------------------------------------------------------------------------------------------
void UFPSGameInstance::CraftModificationSort()
{
	if (!CraftModificationDT.Get())
	{
		UAssetManager::GetStreamableManager().RequestAsyncLoad(CraftModificationDT.ToSoftObjectPath(), [this]()
			{
				AsyncTask(ENamedThreads::GameThread, [this]()
					{
						CraftCreationSort();
					});
			});

		return;
	}

	FString itemsPathNames = {};
	FString contextString = {};
	FText enumText = {};
	TArray<FCraftModificationRecipe*> creationRecipeArray = {};
	TArray<FString> itemsPathArray = {};

	CraftModificationDT.Get()->GetAllRows(contextString, creationRecipeArray);

	for (const FCraftModificationRecipe* item : creationRecipeArray)
	{
		for (const auto& subItem : item->RecipeItems)
		{
			itemsPathArray.Add(subItem.Key.ToSoftObjectPath().ToString());
		}

		itemsPathArray.Sort();

		for (const FString& subItem : itemsPathArray)
		{
			itemsPathNames += subItem;
		}

		ENUM_TO_TEXT(item->ItemType, EItemType, enumText)

		itemsPathNames += enumText.ToString();

		UStatDataSubsystem::ModificationRecipeMap.Add(FName(*itemsPathNames), *item);

		itemsPathArray.Empty();
		itemsPathNames.Empty();
	}
	/*AsyncTask(ENamedThreads::AnyBackgroundThreadNormalTask, [this]()
		{});*/
}
//-----------------------------------------------------------------------------------------------------------