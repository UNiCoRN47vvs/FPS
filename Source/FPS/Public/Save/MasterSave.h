#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "ActorComponents/StorageComponent.h"
#include "ActorComponents/State/StateMasterComponent.h"
#include "Struct/MagazineStruct.h"
#include "Struct/QuestStruct.h"
#include "MasterSave.generated.h"
//-----------------------------------------------------------------------------------------------------------
USTRUCT(BlueprintType)
struct FSaveStruct
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, Category = "Save Game") FCurrency Currency = {};
	UPROPERTY(VisibleAnywhere, Category = "Save Game") TArray<FStorageTab> Inventory = {};
	UPROPERTY(VisibleAnywhere, Category = "Save Game") TArray<FStorageTab> Chest = {};
	UPROPERTY(VisibleAnywhere, Category = "Save Game") TArray<FStorageTab> Equip = {};
	UPROPERTY(VisibleAnywhere, Category = "Save Game") TArray<FStorageTab> Upgrade = {};
	UPROPERTY(VisibleAnywhere, Category = "Save Game") TArray<FStorageTab> Craft = {};
	UPROPERTY(VisibleAnywhere, Category = "Save Game") TArray<FQuest> CurrentQuests = {};
	UPROPERTY(VisibleAnywhere, Category = "Save Game") TArray<FQuest> CompletedQuests = {};
	UPROPERTY(VisibleAnywhere, Category = "Save Game") TMap<EStateName, float> StateMap = {};
	UPROPERTY(VisibleAnywhere, Category = "Save Game") FMagazine MagicMagazine = {};
	UPROPERTY(VisibleAnywhere, Category = "Save Game") TMap<FName, bool> InfoMap = {};
#pragma region Public Beta
	UPROPERTY(VisibleAnywhere, Category = "Save Game") int32 DemoCount = 0;
	UPROPERTY(VisibleAnywhere, Category = "Save Game") int64 UnixTime = 0;
#pragma endregion
};
//-----------------------------------------------------------------------------------------------------------
USTRUCT(BlueprintType)
struct FSettingsSave
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, Category = "Settings Save") bool bIsShowFPS;
	UPROPERTY(VisibleAnywhere, Category = "Settings Save") int32 AntiAliasingMethod;
	UPROPERTY(VisibleAnywhere, Category = "Settings Save") int32 MSAACount;

	UPROPERTY(VisibleAnywhere, Category = "Settings Save") float SoundMasterValue;
	UPROPERTY(VisibleAnywhere, Category = "Settings Save") float SoundEffectValue;
	UPROPERTY(VisibleAnywhere, Category = "Settings Save") float SoundMusicValue;
};
//-----------------------------------------------------------------------------------------------------------
UCLASS()
class FPS_API UMasterSave : public USaveGame
{
	GENERATED_BODY()
public:
	UPROPERTY(VisibleAnywhere, Category = "Save Game") TMap<FString, FSaveStruct> MasterSave;
	UPROPERTY(VisibleAnywhere, Category = "Save Game") FSettingsSave SettingsSave;
protected:
};
//-----------------------------------------------------------------------------------------------------------