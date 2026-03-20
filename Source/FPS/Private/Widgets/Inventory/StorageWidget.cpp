#include "Widgets/Inventory/StorageWidget.h"
#include "ActorComponents/StorageComponent.h"
#include "Widgets/Inventory/InventorySlotWidget.h"
#include "Config/ItemMasterDA.h"
//-----------------------------------------------------------------------------------------------------------
void UStorageWidget::NativeConstruct()
{
	Super::NativeConstruct();
}
//-----------------------------------------------------------------------------------------------------------
void UStorageWidget::InitStorageWidget(UStorageComponent* StorageComponent)
{
	CHECK_PTR(StorageComponent)

	StorageComp = StorageComponent;

	int32 Row = 0;
	int32 Column = 0;
	int32 InvSlotsPerRow = StorageComponent->InvSlotsPerRow;
	USlotWidget* slotWidget = nullptr;
	const TArray<FItemInvStruct>& Storage = StorageComponent->GetStorage();
	for (int i = 0; i < Storage.Num(); ++i)
	{
		Row    = i / InvSlotsPerRow;
		Column = i % InvSlotsPerRow;
		slotWidget = CreateWidget<USlotWidget>(GetWorld(), SlotWidget);
		if (!slotWidget)
			return;

		slotWidget->Index = i;
		slotWidget->StorageComponent = StorageComponent;
		UniformGridPanel->AddChildToUniformGrid(slotWidget, Row, Column);

		if (Storage[i].ItemCount <= 0)
			StorageComponent->SetItemFromIndex(FItemInvStruct{}, StorageComponent->CurrentActiveInvTab, i);

		slotWidget->UpdateInvSlot(Storage[i].ItemDA ? Storage[i].ItemDA->ItemIcon : nullptr, Storage[i].ItemCount);
	}
}
//-----------------------------------------------------------------------------------------------------------
void UStorageWidget::UpdateSlots()
{
	UInventorySlotWidget* slotWidget = nullptr;
	TArray<UWidget*> widgets = {};

	CHECK_PTR(StorageComp)
	
	const TArray<FItemInvStruct> storage = StorageComp->GetStorage();
	widgets = UniformGridPanel->GetAllChildren();

	for (int32 i = 0; i < widgets.Num(); ++i)
	{
		slotWidget = Cast<UInventorySlotWidget>(widgets[i]);
		if (slotWidget && storage[i].ItemDA)
			slotWidget->UpdateInvSlot(storage[i].ItemDA->ItemIcon, storage[i].ItemCount);
		else
			slotWidget->UpdateInvSlot(nullptr, 0);
	}
}
//-----------------------------------------------------------------------------------------------------------


