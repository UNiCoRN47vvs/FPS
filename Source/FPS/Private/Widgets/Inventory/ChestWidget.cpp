#include "Widgets/Inventory/ChestWidget.h"
#include "Components/ScrollBox.h"
#include "ActorComponents/StorageComponent.h"
#include "Widgets/Inventory/StorageTabButtonWidget.h"
#include "Widgets/Inventory/SortButtonWidget.h"
//-----------------------------------------------------------------------------------------------------------
void UChestWidget::NativeConstruct()
{
	Super::NativeConstruct();
}
//-----------------------------------------------------------------------------------------------------------
void UChestWidget::InitStorageWidget(UStorageComponent* StorageComponent)
{
	Super::InitStorageWidget(StorageComponent);

	UStorageTabButtonWidget* tabButtonWidget = nullptr;

	CHECK_PTR(StorageComp)

	for (int32 i = 0; i < StorageComp->InvMaxTabs; ++i)
	{
		tabButtonWidget = CreateWidget<UStorageTabButtonWidget>(this, WBPStorageTabButtonWidget);
		CHECK_PTR(tabButtonWidget)
		tabButtonWidget->InitStorageTabButtonWidget(i, StorageComp, this);
		StorageTabButtonWidgetArray.Emplace(tabButtonWidget);

		TabsScrollBox->AddChild(tabButtonWidget);

		if (i == StorageComp->CurrentActiveInvTab)
			tabButtonWidget->PlayActiveTabAnimation();
	}

	ButtonSortItemType->InitSortButton(StorageComp);
	ButtonSortItemGrade->InitSortButton(StorageComp);
	ButtonSortItemName->InitSortButton(StorageComp);
}
//-----------------------------------------------------------------------------------------------------------
void UChestWidget::DeactivateAllTabsAnimation()
{
	for (auto& item : StorageTabButtonWidgetArray)
	{
		if(item)
			item->StopAllAnimations();
	}
}
//-----------------------------------------------------------------------------------------------------------
