#include "Widgets/Inventory/StoreWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Components/Button.h"
#include "Components/UniformGridSlot.h"
#include "Components/VerticalBox.h"
#include "Components/TextBlock.h"
#include "SubSystem/EventBus.h"
#include "ActorComponents/Inventory/InventoryComponent.h"
#include "ActorComponents/NPC/NPCStorageComponent.h"
#include "Widgets/Inventory/InventoryButtonWidget.h"
#include "Widgets/Inventory/StoreSlotWidget.h"
#include "Widgets/Inventory/StoreItemWidget.h"
//-----------------------------------------------------------------------------------------------------------
void UStoreWidget::InitStorageWidget(UStorageComponent* StorageComponent)
{
	NPCStorageComponent = Cast<UNPCStorageComponent>(StorageComponent);

	Refresh();

	PTR(UniformGridPanel)->SetVisibility(ESlateVisibility::Collapsed);
	PTR(ResreshButton)->Button->OnClicked.AddDynamic(this, &UStoreWidget::RefreshStore);
}
//-----------------------------------------------------------------------------------------------------------
void UStoreWidget::Refresh()
{
	UStoreItemWidget* storeItemWidget = nullptr;

	CHECK_PTR(NPCStorageComponent)
	const TArray<FItemInvStruct>& storage = NPCStorageComponent->GetStorage();

	PTR(StoreVB)->ClearChildren();

	for (int32 i = 0; i < storage.Num(); ++i)
	{
		storeItemWidget = CreateWidget<UStoreItemWidget>(this, StoreItemWidgetClass);
		if (!storeItemWidget)
		{
			ALARM_LOG
				continue;
		}

		StoreVB->AddChild(storeItemWidget);
		
		storeItemWidget->InitStoreItemWidget(NPCStorageComponent, i);
	}
}
//-----------------------------------------------------------------------------------------------------------
void UStoreWidget::RefreshStore()
{
	CHECK_PTR(NPCStorageComponent)

	if (!InventoryComponent)
	{
		InventoryComponent = GetOwningPlayer()->GetPawn()->FindComponentByClass<UInventoryComponent>();
		CHECK_PTR(InventoryComponent)
	}

	FCurrency currency = { 0.5f };

	if (!InventoryComponent->DoesHaveEnoughCurrency(currency))
		return; // TODO :: Сообщить что не хватает валюты в инвентаре для покупки

	InventoryComponent->SubtractCurrency(currency);
	NPCStorageComponent->RefreshStore();
	UEventBus::OnUpdateCurrencyWidget.ExecuteIfBound();

	UGameplayStatics::PlaySound2D(this, RefreshSound);
	Refresh();
}
//-----------------------------------------------------------------------------------------------------------