#include "Widgets/Inventory/StoreSlotWidget.h"
#include "Engine/StreamableManager.h"
#include "Engine/AssetManager.h"
#include "Struct/ItemForSaleStruct.h"
#include "ActorComponents/NPC/NPCStorageComponent.h"
//-----------------------------------------------------------------------------------------------------------
void UStoreSlotWidget::NativeDestruct()
{
	Super::NativeDestruct();
	OnActiveItem.RemoveAll(this);
}
//-----------------------------------------------------------------------------------------------------------
FReply UStoreSlotWidget::NativeOnMouseButtonDown(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent)
{
	UNPCStorageComponent* NPCStorageComponent = nullptr;
	FString string = {};
	FItemForSaleStruct itemForSale = {};
	TArray<FItemForSaleStruct*> itemsArray = {};
	
	if (MouseEvent.GetEffectingButton() == EKeys::LeftMouseButton)
	{
		if (!StorageComponent)
			return Super::NativeOnMouseButtonDown(MyGeometry, MouseEvent);

		NPCStorageComponent = Cast<UNPCStorageComponent>(StorageComponent);
		if (!NPCStorageComponent || !NPCStorageComponent->ItemDataTable)
			return Super::NativeOnMouseButtonDown(MyGeometry, MouseEvent);

		NPCStorageComponent->ItemDataTable->GetAllRows(string, itemsArray);

		for (const FItemForSaleStruct* item : itemsArray)
		{
			if (NPCStorageComponent->GetStorage()[Index].ItemDA != item->Item)
				continue;

			itemForSale = *item;
			break;
		}
		OnActiveItem.Broadcast(itemForSale);
	}
	return Super::NativeOnMouseButtonDown(MyGeometry, MouseEvent);
}
//-----------------------------------------------------------------------------------------------------------
