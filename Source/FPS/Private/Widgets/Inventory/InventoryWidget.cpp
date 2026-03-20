#include "Widgets/Inventory/InventoryWidget.h"
#include "Components/TextBlock.h"
#include "SubSystem/EventBus.h"
#include "ActorComponents/Inventory/InventoryComponent.h"
#include "ActorComponents/Equipment/EquipmentComponent.h"
#include "Enums/ItemType.h"
#include "Enums/ItemGrade.h"
#include "Widgets/Equipment/EquipmentWidget.h"
#include "Widgets/Inventory/InventorySlotWidget.h"
#include "Widgets/Inventory/InformationWidget.h"
#include "Widgets/Inventory/SortButtonWidget.h"
#include "Config/ItemMasterDA.h"
#include "Struct/ItemInvStruct.h"
//-----------------------------------------------------------------------------------------------------------
void UInventoryWidget::NativeConstruct()
{
	Super::NativeConstruct();

	UEventBus::OnPlaySlotAnimationWidget.BindUObject(this, &UInventoryWidget::PlaySlotAnimation);
	UEventBus::OnUpdateWeight.BindUObject(this, &UInventoryWidget::UpdateWeight);
	UEventBus::OnUpdateCurrencyWidget.BindUObject(this, &UInventoryWidget::UpdateCurrency);
}
//-----------------------------------------------------------------------------------------------------------
void UInventoryWidget::NativeDestruct()
{
	UEventBus::OnPlaySlotAnimationWidget.Unbind();
	UEventBus::OnUpdateWeight.Unbind();
	UEventBus::OnUpdateCurrencyWidget.Unbind();

	if (StorageComponent)
		StorageComponent->OnPickUpItem.RemoveAll(this);
}
//-----------------------------------------------------------------------------------------------------------
void UInventoryWidget::UpdateCurrency()
{
	int32 currency = 0;
	CHECK_CAST(InventoryComponent, UInventoryComponent, StorageComp)

	if (SulfurTB)
	{
		currency = InventoryComponent->GetCurrency().Sulfur * 10;
		SulfurTB->SetText(FText::AsNumber(currency / 10.0f));
	}
}
//-----------------------------------------------------------------------------------------------------------
void UInventoryWidget::PlaySlotAnimation(bool bIsPlay, EItemType itemType)
{
	UEquipmentComponent* equipmentComponent = nullptr;

	if (!IsValid(WBPEquipment) || !UEventBus::OnGetEquipmentComponent.IsBound())
	{
		ALARM_LOG
		return;
	}
	equipmentComponent = UEventBus::OnGetEquipmentComponent.Execute();
	CHECK_PTR(equipmentComponent)

	const TArray<FItemInvStruct>& storage = equipmentComponent->GetStorage();

	for (int32 i = 0; i < storage.Num(); ++i)
	{
		if (bIsPlay)
		{
			if (!storage[i].bOccupied &&  WBPEquipment->SlotWidgetArray[i]->SlotType == itemType)
				WBPEquipment->SlotWidgetArray[i]->PlaySlotAnimation(bIsPlay);
		}
		else
			WBPEquipment->SlotWidgetArray[i]->PlaySlotAnimation(bIsPlay);

	}
}
//-----------------------------------------------------------------------------------------------------------
void UInventoryWidget::UpdateWeight(const float weight)
{
	int32 weightValue = 0;

	if (IsValid(WeightTB))
	{
		weightValue = weight * 10;
		WeightTB->SetText(FText::AsNumber(weightValue / 10.f));
	}
}
//-----------------------------------------------------------------------------------------------------------
void UInventoryWidget::InitStorageWidget(UStorageComponent* storageComponent)
{
	Super::InitStorageWidget(storageComponent);
	UpdateCurrency();

	CHECK_PTR(storageComponent)

	storageComponent->OnPickUpItem.AddDynamic(this, &UInventoryWidget::UpdateWidgetInfo);

	StorageComponent = storageComponent;

	ButtonSortItemType->InitSortButton(StorageComp);
	ButtonSortItemGrade->InitSortButton(StorageComp);
	ButtonSortItemName->InitSortButton(StorageComp);
}
//-----------------------------------------------------------------------------------------------------------
void UInventoryWidget::UpdateWidgetInfo()
{
	UpdateSlots();
	UpdateCurrency();
}
//-----------------------------------------------------------------------------------------------------------
