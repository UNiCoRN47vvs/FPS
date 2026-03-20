#include "Widgets/Inventory/StoreItemWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Components/WrapBox.h"
#include "Components/Button.h"
#include "Components/SizeBox.h"
#include "FPS/FPSCharacter.h"
#include "Widgets/Inventory/InventorySlotWidget.h"
#include "ActorComponents/NPC/NPCStorageComponent.h"
#include "ActorComponents/Inventory/InventoryComponent.h"
#include "Struct/ItemForSaleStruct.h"
//-----------------------------------------------------------------------------------------------------------
void UStoreItemWidget::InitStoreItemWidget(UNPCStorageComponent* storageComponent, int32 itemIndex)
{
	CHECK_PTR(storageComponent)

	StorageComponent = storageComponent;
	ItemIndex = itemIndex;
	UInventorySlotWidget* slotWidget = nullptr;
	const FItemInvStruct& itemInvStruct = StorageComponent->GetStorage()[ItemIndex];

	ProductWidget->StorageComponent = StorageComponent;
	ProductWidget->Index = ItemIndex;
	ProductWidget->UpdateInvSlot(itemInvStruct.ItemDA->ItemIcon, itemInvStruct.ItemCount);

	if(StorageComponent->ItemsPrice.IsValidIndex(ItemIndex))
		TextBlock->SetText(FText::AsNumber(StorageComponent->ItemsPrice[ItemIndex]->CurrencyPrice.Sulfur));

	for (const auto& item : StorageComponent->ItemsPrice[ItemIndex]->RecipePrice)
	{
		slotWidget = CreateWidget<UInventorySlotWidget>(this, PriceItemWidgetClass);
		if (!slotWidget)
		{
			ALARM_LOG
			continue;
		}

		WrapBox->AddChild(slotWidget);
		slotWidget->UpdateInvSlot(item.Key.LoadSynchronous()->ItemIcon, item.Value, item.Key.LoadSynchronous());
		slotWidget->SizeBox->SetWidthOverride(47.0f);
		slotWidget->SizeBox->SetHeightOverride(47.0f);
	}

	PTR(BuyButton)->OnClicked.AddDynamic(this, &UStoreItemWidget::BuyItem);
}
//-----------------------------------------------------------------------------------------------------------
void UStoreItemWidget::BuyItem()
{
	CHECK_PTR(GetOwningPlayer())
	CHECK_CAST(PlayerCharacter, AFPSCharacter, GetOwningPlayer()->GetCharacter())

	int32 itemCount = StorageComponent->GetStorage()[ItemIndex].ItemCount;
	int32 count = 0;
	UInventoryComponent* invComponent = nullptr;
	FItemInvStruct itemInv = {};
	invComponent = PlayerCharacter->GetInventoryComponent();
	CHECK_PTR(invComponent)

	const TArray<FItemInvStruct>& storage = invComponent->GetStorage();
	if (!invComponent->DoesHaveEnoughCurrency(StorageComponent->ItemsPrice[ItemIndex]->CurrencyPrice))
	{
		UGameplayStatics::PlaySound2D(this, NoMoneySound);
		return; // TODO :: Сообщить что не хватает предметов в инвентаре для покупки
	}

	for (auto& item : StorageComponent->ItemsPrice[ItemIndex]->RecipePrice)
	{
		count = item.Value;
		for (int32 i = 0; i < storage.Num(); ++i)
		{
			if (storage[i].ItemDA == item.Key.LoadSynchronous())
			{
				if (storage[i].ItemCount >= count)
					break;
				else
					count -= storage[i].ItemCount;
			}

			if (i >= storage.Num() - 1 && count > 0)
			{
				UGameplayStatics::PlaySound2D(this, NoMoneySound);
				return; // TODO :: Сообщить что не хватает предметов в инвентаре для покупки
			}
		}
	} 

	for (auto& item : StorageComponent->ItemsPrice[ItemIndex]->RecipePrice)
	{
		count = item.Value;
		for (int32 i = 0; i < storage.Num(); ++i)
		{
			if (storage[i].ItemDA == item.Key.LoadSynchronous())
			{
				itemInv = storage[i];

				if (itemInv.ItemCount >= count)
				{
					itemInv.ItemCount -= count;
					invComponent->SetItemFromIndex(itemInv, invComponent->CurrentActiveInvTab, i);
					break;
				}
				else
				{
					count -= itemInv.ItemCount;
					itemInv = {};
					invComponent->SetItemFromIndex(itemInv, invComponent->CurrentActiveInvTab, i);
				}

			}
		}
	}

	invComponent->SubtractCurrency(StorageComponent->ItemsPrice[ItemIndex]->CurrencyPrice);
	invComponent->PickUpItem(itemCount, StorageComponent->ItemsPrice[ItemIndex]->Item);
	UGameplayStatics::PlaySound2D(this, BuySound);

}
//-----------------------------------------------------------------------------------------------------------