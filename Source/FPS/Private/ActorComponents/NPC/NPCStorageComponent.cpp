#include "ActorComponents/NPC/NPCStorageComponent.h"
#include "Engine/StreamableManager.h"
#include "Engine/AssetManager.h"
#include "Struct/ItemForSaleStruct.h"
//-----------------------------------------------------------------------------------------------------------
void UNPCStorageComponent::InitNPCStorage(UDataTable* dataTable)
{
	CHECK_PTR(dataTable)

	ItemDataTable = dataTable;
	
	RefreshStore();
}
//-----------------------------------------------------------------------------------------------------------
void UNPCStorageComponent::RefreshStore()
{
	UDataTable* data = nullptr;
	int32 storageSlotCount = 12;
	int32 randomIndex = 0;
	int32 arrayLength = 0;

	FString string = {};
	FItemInvStruct itemStruct = {};
	TMap<int32, int32> mapIndexes = {};
	TArray<FItemForSaleStruct*> itemsArray = {};

	PTR(ItemDataTable)->GetAllRows(string, itemsArray);

	arrayLength = itemsArray.Num();

	InvMaxSlots = arrayLength < storageSlotCount ? arrayLength : storageSlotCount;

	storageSlotCount = InvMaxSlots;

	Storage[0].StorageTab.Empty();
	ItemsPrice.Empty();
	Storage.Empty();

	Storage.Emplace(FStorageTab{});

	do
	{
		randomIndex = FMath::RandRange(0, arrayLength - 1);

		if (mapIndexes.Contains(randomIndex)
			|| !itemsArray.IsValidIndex(randomIndex) 
			|| !itemsArray[randomIndex] 
			|| !itemsArray[randomIndex]->Item)
			continue;

		mapIndexes.Add(randomIndex, 0);
		--storageSlotCount;

		itemStruct = {};
		itemStruct.bOccupied = true;
		itemStruct.ItemCount = itemsArray[randomIndex]->Count;
		itemStruct.ItemDA = itemsArray[randomIndex]->Item;
		itemStruct.ItemLevel = 0;
		itemStruct.StatValue = itemsArray[randomIndex]->Item->StatStruct.FindRandomStatWithRandomValue(itemStruct.ItemDA->ItemGrade);

		Storage[0].StorageTab.Add(itemStruct);
		ItemsPrice.Add(itemsArray[randomIndex]);
	} while (storageSlotCount > 0);

	OnRefreshStore.Broadcast();
}
//-----------------------------------------------------------------------------------------------------------
