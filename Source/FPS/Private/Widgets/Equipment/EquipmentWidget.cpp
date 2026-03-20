#include "Widgets/Equipment/EquipmentWidget.h"
#include "FPS/FPSCharacter.h"
#include "Components/SizeBox.h"
#include "Widgets/Inventory/InventorySlotWidget.h"
#include "Config/ItemMasterDA.h"
//-----------------------------------------------------------------------------------------------------------
void UEquipmentWidget::NativeConstruct()
{
	Super::NativeConstruct();
}
//-----------------------------------------------------------------------------------------------------------
void UEquipmentWidget::InitEquipmentWidget(UStorageComponent* storageComponent)
{
	CHECK_PTR(storageComponent)

	const TArray<FItemInvStruct>& storage = storageComponent->GetStorage();
	TArray<UInventorySlotWidget*> array = {};
	GetAllInventorySlotWidgetsIn(SizeBox, SlotWidgetArray);

	for (int i = 0; i < storage.Num(); ++i)
	{
		for (auto& item : SlotWidgetArray)
		{
			if (item->Index == i)
			{
				item->StorageComponent = storageComponent;
				item->UpdateInvSlot(storage[i].ItemDA ? storage[i].ItemDA->ItemIcon : nullptr, storage[i].ItemCount);
				array.Add(item);
				break;
			}
		}
	}

	SlotWidgetArray = array;
}
//-----------------------------------------------------------------------------------------------------------
void UEquipmentWidget::GetAllInventorySlotWidgetsIn(UWidget* parentWidget, TArray<UInventorySlotWidget*>& outWidgets)
{
	int32 childCount = 0;
	UWidget* child = nullptr;
	UInventorySlotWidget* slotWidget = nullptr;
	UPanelWidget* panel = Cast<UPanelWidget>(parentWidget);
	CHECK_PTR(panel) //UTextBlock не UPanelWidget

	childCount = panel->GetChildrenCount(); // Получаем количество детей у панели
	for (int32 i = 0; i < childCount; i++) // Проходим по каждому ребенку панели
	{
		child = panel->GetChildAt(i);
		slotWidget = Cast<UInventorySlotWidget>(child);
		if (slotWidget) // Проверяем, является ли ребенок UUserWidget	
		{
			outWidgets.Add(slotWidget); // Добавляем UUserWidget в массив
			continue;
		}
		GetAllInventorySlotWidgetsIn(child, outWidgets); // Рекурсивно проверяем детей текущего ребенка
	}
}
//-----------------------------------------------------------------------------------------------------------
