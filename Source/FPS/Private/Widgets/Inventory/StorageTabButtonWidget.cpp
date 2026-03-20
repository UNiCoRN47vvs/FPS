#include "Widgets/Inventory/StorageTabButtonWidget.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "ActorComponents/StorageComponent.h"
#include "Widgets/Inventory/ChestWidget.h"
//-----------------------------------------------------------------------------------------------------------
void UStorageTabButtonWidget::InitStorageTabButtonWidget(int32 Index, UStorageComponent* Storage, UChestWidget* Widget)
{
	StorageComponent = Storage;
	StorageWidget = Widget;
	IndexTab = Index;
	TabNumberText->SetText(FText::AsNumber(Index + 1));
	TabButton->OnClicked.AddDynamic(this, &UStorageTabButtonWidget::SetNewActiveCurrentTab);
}
//-----------------------------------------------------------------------------------------------------------
void UStorageTabButtonWidget::SetNewActiveCurrentTab()
{
	CHECK_PTR(StorageWidget)

	StorageComponent->CurrentActiveInvTab = IndexTab;
	StorageWidget->DeactivateAllTabsAnimation();
	StorageWidget->UpdateSlots();
	PlayActiveTabAnimation();
}
//-----------------------------------------------------------------------------------------------------------
void UStorageTabButtonWidget::PlayActiveTabAnimation()
{
	PlayAnimation(ActiveTabAnimation, 0.0, 0);
}
//-----------------------------------------------------------------------------------------------------------