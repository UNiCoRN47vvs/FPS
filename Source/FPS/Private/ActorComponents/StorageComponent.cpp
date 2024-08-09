#include "ActorComponents/StorageComponent.h"
//-----------------------------------------------------------------------------------------------------------
UStorageComponent::UStorageComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}
//-----------------------------------------------------------------------------------------------------------
void UStorageComponent::BeginPlay()
{
	Super::BeginPlay();
	for (int i = 0; i < InvMaxSlots; i++)
	{
		Storage.Add(FItemInvStruct{});
	}

	InitInvWidget.Broadcast(this);
}
//-----------------------------------------------------------------------------------------------------------
//Getter
TArray<FItemInvStruct> UStorageComponent::GetStorage()
{
	return Storage;
}
//-----------------------------------------------------------------------------------------------------------
void UStorageComponent::SetItemFromIndex(FItemInvStruct Item, int Index)
{
	Storage[Index] = Item;
}
