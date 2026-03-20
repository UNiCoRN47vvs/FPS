#include "ActorComponents/StorageComponent.h"
#include "SubSystem/EventBus.h"
#include "FPS/FPSPlayerController.h"
#include "Widgets/Inventory/InventorySlotWidget.h"
#include "Config/ItemMasterDA.h"
#include "Config/CurrencyMasterDA.h"
#include "Struct/ItemInvStruct.h"
//-----------------------------------------------------------------------------------------------------------
UStorageComponent::UStorageComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	Currency = {};
	FastDropStorage = {};
	InvMaxSlots = {};
	InvSlotsPerRow = {};
	MainHUDWidget = nullptr;
	PlayerCharacter = nullptr;
	PlayerController = nullptr;
	StorageType = {};
	Storage = {};
}
//-----------------------------------------------------------------------------------------------------------
void UStorageComponent::BeginPlay()
{
	Super::BeginPlay();
	InitStorage();
}
//-----------------------------------------------------------------------------------------------------------
void UStorageComponent::OnComponentDestroyed(bool bDestroyingHierarchy)
{
	OnPickUpItem.RemoveAll(this);
	Super::OnComponentDestroyed(bDestroyingHierarchy);
}
//-----------------------------------------------------------------------------------------------------------
void UStorageComponent::InitStorage()
{
	for (int32 i = 0; i <= InvMaxTabs; ++i)
	{
		Storage.Emplace(FStorageTab{});
		for (int32 j = 0; j < InvMaxSlots; ++j)
		{
			Storage[i].StorageTab.Emplace(FItemInvStruct{});
		}
	}
}
//-----------------------------------------------------------------------------------------------------------
//Getter
const TArray<FItemInvStruct>& UStorageComponent::GetStorage()
{
	return Storage[CurrentActiveInvTab].StorageTab;
}
const TArray<FStorageTab>& UStorageComponent::GetAllStorageTabs()
{
	return Storage;
}
EStorageType UStorageComponent::GetStorageType()
{
	return StorageType;
}
//-----------------------------------------------------------------------------------------------------------
bool UStorageComponent::IsStorageEmpty()
{
	for (const FItemInvStruct& item : Storage[CurrentActiveInvTab].StorageTab)
	{
		if (item.bOccupied)
			return false;
	}
	
	return true;
}
//-----------------------------------------------------------------------------------------------------------
bool UStorageComponent::PickUpItem(int32& itemCount, UItemMasterDA* itemDA, int32 itemLevel, const FStatValueStruct statValueStruct)
{
	bool bFoundEmptySlot = false;
	EElementsType elementsType = EElementsType::None;
	int32 emptySlot = 0;
	FItemInvStruct itemStruct = {};
	TArray<FItemInvStruct>& storage = Storage[CurrentActiveInvTab].StorageTab;

	if (!itemDA)
	{
		ALARM_LOG
		return false;
	}
	
	itemStruct.bOccupied			= true;
	itemStruct.ItemDA				= itemDA;
	itemStruct.ItemCount			= itemCount;
	itemStruct.ItemLevel			= itemLevel;
	itemStruct.StatValue			= statValueStruct;

	//TODO :: Изменить с учетом перегруженной функции
	if (itemStruct.ItemDA->ItemType == EItemType::Currency)
	{
		//Изменить для множества валют!!!!!!!!!
		Currency.Sulfur += itemCount;
		OnPickUpItem.Broadcast();
		return true;
	}

	bool borosBool1	= false;
	bool borosBool2	= false;
	bool borosBool3   = false;
	bool borosBool4   = false;
	bool borosBool5	= false;

	for (int32 i = 0; i < storage.Num(); ++i) // Поиск слота для предмета в инвентаре
	{
		if (storage[i].bOccupied) // Если слот занят, проверяем можно ли сложить предметы
		{
			if (!storage[i].ItemDA)
			{
				ALARM_LOG
				return false;
			}

			borosBool1 = storage[i].ItemDA->ItemName		!= itemStruct.ItemDA->ItemName;
			borosBool2 = storage[i].ItemCount				== storage[i].ItemDA->ItemCountMax;
			borosBool3 = storage[i].ItemDA->ItemGrade		!= itemStruct.ItemDA->ItemGrade;
			borosBool4 = storage[i].ItemDA->ElementType	!= itemStruct.ItemDA->ElementType;
			borosBool5 = storage[i].ItemLevel				!= itemStruct.ItemLevel;

			if (borosBool1 || borosBool2 || borosBool3 || borosBool4 || borosBool5) // Если количество предметов не превышает максимум, добавляем предметы в слот
				continue;

			if (storage[i].ItemCount + itemStruct.ItemCount <= storage[i].ItemDA->ItemCountMax)
			{
				storage[i].ItemCount += itemStruct.ItemCount;
				itemCount = 0;
				OnPickUpItem.Broadcast();
				return true;
			}
			else
			{
				// Если количество превышает максимум, добавляем столько, сколько влезет
				int32 difference = storage[i].ItemDA->ItemCountMax - storage[i].ItemCount;
				itemStruct.ItemCount -= difference;
				itemCount = itemStruct.ItemCount;
				storage[i].ItemCount = storage[i].ItemDA->ItemCountMax;
				continue;
			}
		}
		else if (!bFoundEmptySlot) // Если слот не занят, запоминаем первый свободный слот
		{
			emptySlot = i;
			bFoundEmptySlot = true;
		}
	}

	if(bFoundEmptySlot) // Если найден пустой слот, кладем предмет туда
	{
		if (itemStruct.ItemCount > itemStruct.ItemDA->ItemCountMax)
		{
			int32 count = itemStruct.ItemCount;
			int32 difference = count - itemStruct.ItemDA->ItemCountMax;
			storage[emptySlot] = itemStruct;
			storage[emptySlot].bOccupied = true;
			storage[emptySlot].ItemCount = storage[emptySlot].ItemDA->ItemCountMax;
			itemStruct.ItemCount = difference;
			itemCount = difference;
			count = itemStruct.ItemCount;
			// Рекурсивно добавляем оставшиеся предметы
			return PickUpItem(itemCount, itemDA);
		}

		storage[emptySlot] = itemStruct;
		storage[emptySlot].bOccupied = true;
		itemCount = 0;
		OnPickUpItem.Broadcast();
		return true;
	}
	return false;
}
//-----------------------------------------------------------------------------------------------------------
bool UStorageComponent::PickUpItem(const FCurrency& pickUpCurrency)
{
	//Изменить для множества валют!!!!!!!!!
	Currency += pickUpCurrency;
	OnPickUpItem.Broadcast();
	return true;
}
//-----------------------------------------------------------------------------------------------------------
void UStorageComponent::InitArmorStat()
{
}
//-----------------------------------------------------------------------------------------------------------
void UStorageComponent::RefreshMagazine(int32 index)
{
}
//-----------------------------------------------------------------------------------------------------------
void UStorageComponent::ApplyFastDrop(AFPSPlayerController* controller, int32 index, UInventorySlotWidget* widgetSlot)
{
	if(!PlayerController)
		PlayerController = controller;

	CHECK_PTR(PlayerController)

	if(PlayerController->GetApplyFastDropInfo(FastDropStorage, GetStorage()[index]))
		Storage[CurrentActiveInvTab].StorageTab[index] = {};

	if(GetStorage()[index].ItemDA)
		widgetSlot->UpdateInvSlot(GetStorage()[index].ItemDA->ItemIcon, GetStorage()[index].ItemCount);
	else
		widgetSlot->UpdateInvSlot(nullptr, 0);
	
	UEventBus::OnWeightCalculation.ExecuteIfBound();
}
//-----------------------------------------------------------------------------------------------------------
void UStorageComponent::SetItemFromIndex(FItemInvStruct item, int32 indexTab, int32 indexStorage)
{
	if (!Storage.IsValidIndex(indexTab))
		return;

	if(item.ItemCount <= 0)
		item = FItemInvStruct{};

	Storage[indexTab].StorageTab[indexStorage] = item;

	switch (StorageType)
	{
	case EStorageType::Chest:
	case EStorageType::TreasureInventory:
	case EStorageType::Upgrade:
	case EStorageType::Portal:
	case EStorageType::Craft:
		break;

	case EStorageType::Inventory:
		if (item.ItemDA && item.ItemDA->ItemType == EItemType::Currency)
		{
			Storage[indexTab].StorageTab[indexStorage] = {};

			PickUpItem(item.ItemCount, item.ItemDA);
		}
		break;

	case EStorageType::Equipment:
		RefreshMagazine(indexStorage);
		InitArmorStat();
		break;
	}

	UEventBus::OnSetItemFromIndexWidget.ExecuteIfBound(StorageType, indexStorage, GetStorage());
	UEventBus::OnWeightCalculation.ExecuteIfBound();
}
//-----------------------------------------------------------------------------------------------------------
