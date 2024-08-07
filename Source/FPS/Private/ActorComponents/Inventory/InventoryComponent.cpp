#include "ActorComponents/Inventory/InventoryComponent.h"
//-----------------------------------------------------------------------------------------------------------
UInventoryComponent::UInventoryComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}
//-----------------------------------------------------------------------------------------------------------
//Getter
TArray<FItemInvStruct> UInventoryComponent::GetInventory()
{
	return TArray<FItemInvStruct>();
}
//-----------------------------------------------------------------------------------------------------------
void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();
	for (int i = 0; i < InvMaxSlots; i++)
	{
		Inventory.Add(FItemInvStruct{});
	}
}
//-----------------------------------------------------------------------------------------------------------
bool UInventoryComponent::PickUpItem(FItemInvStruct& ItemStruct)
{
	for (auto& item : Inventory)
	{
		if (item.bOccupied)
		{
			if (item.ItemName != ItemStruct.ItemName || item.ItemCount == item.ItemCountMax)
				continue;

			if (item.ItemCount + ItemStruct.ItemCount <= item.ItemCountMax)
			{
				item.ItemCount += ItemStruct.ItemCount;
				return true;
			}
			else
			{
				int LocalDifference = item.ItemCountMax - item.ItemCount;
				ItemStruct.ItemCount -= LocalDifference;
				item.ItemCount = item.ItemCountMax;
				continue;
			}
		}

		if (ItemStruct.ItemCount > item.ItemCountMax)
		{
			int LocalCount = ItemStruct.ItemCount;
			int LocalDifference = LocalCount - ItemStruct.ItemCountMax;
			item = ItemStruct;
			item.bOccupied = true;
			item.ItemCount = item.ItemCountMax;
			ItemStruct.ItemCount = LocalDifference;
			return PickUpItem(ItemStruct);
		}

		item = ItemStruct;
		item.bOccupied = true;
		return true;
	}
	return false;
}