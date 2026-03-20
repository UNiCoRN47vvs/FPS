#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Engine/AssetManager.h"
#include "MainGameConfig.generated.h"
//-----------------------------------------------------------------------------------------------------------
USTRUCT(BlueprintType)
struct FConfigTable : public FTableRowBase
{
   GENERATED_BODY()
   UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item Struct")	FName NameID;
   UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item Struct")	TSoftObjectPtr<UPrimaryDataAsset> Config;
};
//-----------------------------------------------------------------------------------------------------------
UCLASS()
class FPS_API UMainGameConfig : public UPrimaryDataAsset
{
	GENERATED_BODY()
public:
   static UMainGameConfig* GetInstance()
   {
      if (LIKELY(Instance != nullptr))
         return Instance;

      // Получаем Asset Manager
      UAssetManager& Manager = UAssetManager::Get();

      // Создаем массив для хранения данных о найденных ассетах
      TArray<FAssetData> AssetDataList;

      // Получаем тип актива, используя имя текущего класса
      const FPrimaryAssetType Type(StaticClass()->GetFName());

      // Заполняем массив AssetDataList данными ассетов, соответствующих типу
      Manager.GetPrimaryAssetDataList(Type, AssetDataList);

      // Проходим по всем найденным ассетам
      for (auto& AssetData : AssetDataList)
      {
         // Загружаем ассет синхронно и сохраняем его в переменную Instance
         Instance = Cast<UMainGameConfig>(AssetData.GetAsset());
         if (Instance != nullptr)
            break;
      }

      return Instance;
   }

private:
   // Синглтон для хранения единственного экземпляра этого класса
   static UMainGameConfig* Instance;
};
//-----------------------------------------------------------------------------------------------------------