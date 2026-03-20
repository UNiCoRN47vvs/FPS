#include "ActorComponents/Drop/DropComponent.h"
#include "Engine/StreamableManager.h"
#include "Engine/AssetManager.h"
#include "SubSystem/WorldRuler.h"
#include "ActorComponents/StorageComponent.h"
#include "Struct/ItemGradeChance.h"
#include "Struct/ItemTypeData.h"
#include "Struct/ItemDataStruct.h"
#include "Config/ItemMasterDA.h"
#include "Config/ItemGradeColorDA.h"
#include "Interfaces/DropInterface.h"
//-----------------------------------------------------------------------------------------------------------
UDropComponent::UDropComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}
//-----------------------------------------------------------------------------------------------------------
void UDropComponent::BeginPlay()
{
	Super::BeginPlay();
}
//-----------------------------------------------------------------------------------------------------------
void UDropComponent::SearchDrop(UDataTable* dataTable)
{
	if (!WorldRuler)
	{
		WorldRuler = GetWorld()->GetSubsystem<UWorldRuler>();
		CHECK_PTR(WorldRuler)
	}

	AsyncTask(ENamedThreads::AnyBackgroundThreadNormalTask, [&, dataTable]()
		{
			bool bIsSecondChance = false;

			int32 currentInventorySlotCount = 0;
			int32 maxInventorySlotCount = 10;

			FItemTypeData* typeDataRow = nullptr;
			FItemTypeChance* rowTypeDT = nullptr;
			FItemGradeChance* rowGradeDT = nullptr;
			FItemDataStruct* rowItemDT = nullptr;
			FItemDataStruct* subRowItemDT = nullptr;

			float chance = 0.0;
			float allChances = 0.0;
			float chanceCounter = 0.0;
			
			FStuffing lootDropStruct = {};
			TArray<ETypeChance> typeStorage = {};
			TArray<FStuffing> lootDrop = {};

			CHECK_PTR(WorldRuler)
				
			FPortalStat portalStat = WorldRuler->GetPortalStat();

			CHECK_PTR(portalStat.TypeChanceTable)
			CHECK_PTR(portalStat.GradeChanceTable)
			CHECK_PTR(portalStat.ItemTypeTable)

			if (dataTable) 
			{
				//Поиск рандомного дополнительного лута из таблицы
				for (FName& item : dataTable->GetRowNames())
				{
					subRowItemDT = dataTable->FindRow<FItemDataStruct>(item, TEXT(""));
					if (!subRowItemDT)
						continue;

					chance = FMath::FRandRange(0.0, 100.0);

					if (subRowItemDT->Chance < chance || static_cast<int32>(subRowItemDT->ItemGrade) > static_cast<int32>(portalStat.Grade))
						continue;

					if (lootDrop.Num() >= maxInventorySlotCount)
						break;

					lootDropStruct.ItemCount = FMath::RandRange(1, subRowItemDT->DropCountMax);
					lootDropStruct.SoftItemPtr = subRowItemDT->DataAsset;
					lootDrop.Add(lootDropStruct);

					lootDropStruct = {};
				}
			}

			if (lootDrop.Num() >= maxInventorySlotCount)
				StaffingAndSend(lootDrop);

			currentInventorySlotCount += lootDrop.Num();

			do
			{
				chance = FMath::FRandRange(0.0f, portalStat.AllTypeChances);
				chanceCounter = 0.0;

				for (const FName& item : portalStat.TypeChanceTable->GetRowNames())
				{
					rowTypeDT = portalStat.TypeChanceTable->FindRow<FItemTypeChance>(item, TEXT(""));

					if (rowTypeDT->ItemType == ETypeChance::SecondChance)
					{
						bIsSecondChance = rowTypeDT->Chance + portalStat.GetValueFromSecondChance() > FMath::RandRange(0.0f, 100.0f);
						continue;
					}

					if (rowTypeDT->ItemType == ETypeChance::Fail)
						chanceCounter += rowTypeDT->Chance - portalStat.GetValueFromFailChance() <= 0.0 ? 0.0 : rowTypeDT->Chance - portalStat.GetValueFromFailChance();
					else
						chanceCounter += rowTypeDT->Chance;

					if (chance <= chanceCounter)
					{
						if (rowTypeDT->ItemType == ETypeChance::Fail)
							break;

						typeStorage.Add(rowTypeDT->ItemType);
						++currentInventorySlotCount;
						break;
					}
				}

			} while (bIsSecondChance && currentInventorySlotCount < maxInventorySlotCount);

			if (typeStorage.IsEmpty() && lootDrop.IsEmpty())
				return;

			for (ETypeChance item : typeStorage)
			{
				//Поиск грейда из шанса
				chance = FMath::RandRange(0.0f, portalStat.AllGradeChances);
				chanceCounter = 0.0;

				for (const FName& subItem : portalStat.GradeChanceTable->GetRowNames())
				{
					rowGradeDT = portalStat.GradeChanceTable->FindRow<FItemGradeChance>(subItem, TEXT(""));
					if (rowGradeDT->Chance <= 0.0)
						continue;

					chanceCounter += rowGradeDT->Chance;
					if (chance <= chanceCounter)
						break;
				}

				if (!rowGradeDT)
					continue;

				//Поиск таблицы предметов
				for (const FName& subItem : portalStat.ItemTypeTable->GetRowNames())
				{
					typeDataRow = portalStat.ItemTypeTable->FindRow<FItemTypeData>(subItem, TEXT(""));
					if (typeDataRow && typeDataRow->ItemType == item)
						break;
				}

				if (!typeDataRow || !typeDataRow->DataTable)
					continue;

				//Поиск предмета из шанса
				for (const FName& subItem : typeDataRow->DataTable->GetRowNames())
				{
					rowItemDT = typeDataRow->DataTable->FindRow<FItemDataStruct>(subItem, TEXT(""));
					if (rowItemDT->ItemGrade != rowGradeDT->ItemGrade)
						continue;
					allChances += rowItemDT->Chance;
				}

				chance = FMath::RandRange(0.0f, allChances);

				chanceCounter = 0.0;

				for (const FName& subItem : typeDataRow->DataTable->GetRowNames())
				{
					rowItemDT = typeDataRow->DataTable->FindRow<FItemDataStruct>(subItem, TEXT(""));
					if (rowItemDT->ItemGrade != rowGradeDT->ItemGrade || rowItemDT->Chance <= 0.0)
						continue;

					chanceCounter += rowItemDT->Chance;
					if (chance <= chanceCounter)
						break;
				}

				if (!rowItemDT)
					continue;
				lootDropStruct.ItemCount = FMath::RandRange(1, rowItemDT->DropCountMax);
				lootDropStruct.SoftItemPtr = rowItemDT->DataAsset;

				lootDrop.Add(lootDropStruct);
				lootDropStruct = {};
			}

			StaffingAndSend(lootDrop);
		});
}
//-----------------------------------------------------------------------------------------------------------
void UDropComponent::StaffingAndSend(TArray<FStuffing> dropItems)
{
	AsyncTask(ENamedThreads::GameThread, [&, dropItems]()
		{
			UItemMasterDA* itemMasterDA = nullptr; 
			IDropInterface* dropInterface = nullptr;
			FLinearColor color = {};
			FItemInvStruct item = {};
			TArray<FSoftObjectPath> assetsToLoad = {};

			for (const FStuffing& subItem : dropItems)
			{
				if (!subItem.SoftItemPtr.Get())
					assetsToLoad.Add(subItem.SoftItemPtr.ToSoftObjectPath());
			}

			if (!assetsToLoad.IsEmpty())
			{
				UAssetManager::GetStreamableManager().RequestAsyncLoad(assetsToLoad, [this, dropItems]()
					{
						if (this)
							this->StaffingAndSend(dropItems);
					});

				return;
			}


			dropInterface = Cast<IDropInterface>(GetOwner());
			CHECK_PTR(dropInterface)

			for (const FStuffing& subItem : dropItems)
			{
				itemMasterDA = Cast<UItemMasterDA>(subItem.SoftItemPtr.Get());
				CHECK_PTR(itemMasterDA)

				item = {};
				item.bOccupied = true;
				item.ItemDA = itemMasterDA;
				item.ItemCount = subItem.ItemCount;
				item.ItemLevel = 0;
				item.StatValue = itemMasterDA->StatStruct.FindRandomStatWithRandomValue(itemMasterDA->ItemGrade);
			
				if (ItemGradeColorData)
				{
					switch (itemMasterDA->ItemGrade)
					{
					case EItemGrade::White:
						color = ItemGradeColorData->ColorGradeWhite;
						break;

					case EItemGrade::Green:
						color = ItemGradeColorData->ColorGradeGreen;
						break;

					case EItemGrade::Blue:
						color = ItemGradeColorData->ColorGradeBlue;
						break;

					case EItemGrade::Epic:
						color = ItemGradeColorData->ColorGradeEpic;
						break;

					case EItemGrade::Legendary:
						color = ItemGradeColorData->ColorGradeLegendary;
						break;

					default:
						break;
					}
				}

				dropInterface->ApplyDrop(item, LootEffect, color);
			}

		});
}
//-----------------------------------------------------------------------------------------------------------