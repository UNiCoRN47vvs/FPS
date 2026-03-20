#include "Widgets/Dialog/DialogWidget.h"
#include "Components/Button.h"
#include "Widgets/MainHUD/MainHUDWidget.h"
#include "Widgets/Inventory/InventoryButtonWidget.h"
#include "ActorComponents/StorageComponent.h"
//-----------------------------------------------------------------------------------------------------------
void UDialogWidget::InitDialogWidget(UStorageComponent* storageComp, UMainHUDWidget* mainHUDWidget)
{
	StorageComponent = storageComp;
	MainHUD = mainHUDWidget;
	PTR(BuyButton)->Button->OnClicked.AddDynamic(this, &UDialogWidget::ApplyBuyButton);
	PTR(QuestButton)->Button->OnClicked.AddDynamic(this, &UDialogWidget::ApplyQuestButton);
	PTR(CloseButton)->Button->OnClicked.AddDynamic(this, &UDialogWidget::ApplyCloseButton);
}
//-----------------------------------------------------------------------------------------------------------
void UDialogWidget::ApplyBuyButton()
{
	CHECK_WEAK_PTR(MainHUD)
		CHECK_WEAK_PTR(StorageComponent)
	MainHUD->CreateWidgetByType(StorageComponent->GetStorageType(), StorageComponent.Get());
	MainHUD->WBPDialog = nullptr;
	RemoveFromParent();
}
//-----------------------------------------------------------------------------------------------------------
void UDialogWidget::ApplyQuestButton()
{
	CHECK_WEAK_PTR(MainHUD)
	CHECK_WEAK_PTR(StorageComponent)

	MainHUD->CreateWidgetByType(EStorageType::Quests, StorageComponent.Get(), StorageComponent->GetOwner());
	MainHUD->WBPDialog = nullptr;
	RemoveFromParent();
}
//-----------------------------------------------------------------------------------------------------------
void UDialogWidget::ApplyCloseButton()
{
	CHECK_WEAK_PTR(MainHUD)
	CHECK_WEAK_PTR(StorageComponent)

	RemoveFromParent();
	MainHUD->OnSetWidgetInputMode.ExecuteIfBound(false);
	MainHUD->WBPDialog = nullptr;
}
//-----------------------------------------------------------------------------------------------------------