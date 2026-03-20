#include "ActorComponents/Chest/ChestComponent.h"
#include "FPS/FPSPlayerController.h"
#include "Widgets/Inventory/InventorySlotWidget.h"
//-----------------------------------------------------------------------------------------------------------
UChestComponent::UChestComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}
//-----------------------------------------------------------------------------------------------------------
void UChestComponent::BeginPlay()
{
	Super::BeginPlay();
}
//-----------------------------------------------------------------------------------------------------------
void UChestComponent::ApplyFastDrop(AFPSPlayerController* Controller, int32 Index, UInventorySlotWidget* WidgetSlot)
{
	FastDropStorage = EStorageType::Chest;
	Super::ApplyFastDrop(Controller, Index, WidgetSlot);
}
