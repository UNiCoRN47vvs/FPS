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