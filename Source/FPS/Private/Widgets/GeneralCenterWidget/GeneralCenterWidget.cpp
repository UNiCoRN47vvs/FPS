#include "Widgets/GeneralCenterWidget/GeneralCenterWidget.h"
#include "Components/WidgetSwitcher.h"
#include "Components/Button.h"
#include "SubSystem/EventBus.h"
#include "FPS/FPSCharacter.h"
#include "ActorComponents/Inventory/InventoryComponent.h"
#include "ActorComponents/Equipment/EquipmentComponent.h"
#include "ActorComponents/Chest/ChestComponent.h"
#include "ActorComponents/Portal/PortalComponent.h"
#include "ActorComponents/Upgrade/UpgradeComponent.h"
#include "Widgets/Inventory/InventoryButtonWidget.h"
#include "Widgets/Inventory/InventoryWidget.h"
#include "Widgets/Equipment/EquipmentWidget.h"
#include "Widgets/Inventory/ChestWidget.h"
#include "Widgets/Upgrade/UpgradeWidget.h"
#include "Widgets/Portal/PortalWidget.h"
#include "Widgets/Inventory/StoreWidget.h"
#include "Widgets/Quest/QuestsWidget.h"
#include "Widgets/Inventory/InventorySlotWidget.h"
#include "Widgets/Info/InformationStandWidget.h"
#include "Widgets/Craft/CraftWidget.h"
//-----------------------------------------------------------------------------------------------------------
void UGeneralCenterWidget::NativeConstruct()
{
	CHECK_PTR(InventoryButton)
	CHECK_PTR(QuestsButton)

	PTR(InventoryButton)->Button->OnClicked.AddDynamic(this, &UGeneralCenterWidget::ShowInventory);
	PTR(QuestsButton)->Button->OnClicked.AddDynamic(this, &UGeneralCenterWidget::ShowQuests);
	PTR(InfoWidgetButton)->Button->OnClicked.AddDynamic(this, &UGeneralCenterWidget::ShowInfoWidget);

	UEventBus::OnSetItemFromIndexWidget.BindUObject(this, &UGeneralCenterWidget::SetItemFromIndexWidget);
	UEventBus::OnClickInfoButton.BindUObject(this, &UGeneralCenterWidget::ClickInfoButton);
}
//-----------------------------------------------------------------------------------------------------------
void UGeneralCenterWidget::NativeDestruct()
{
	Super::NativeDestruct();
	PTR(CloseButton)->OnClicked.RemoveAll(this);

	UEventBus::OnSetItemFromIndexWidget.Unbind();
	UEventBus::OnClickInfoButton.Unbind();
}
//-----------------------------------------------------------------------------------------------------------
//Getters
UStorageComponent* UGeneralCenterWidget::GetCurrentActiveStorage()
{
	if (!IsValid(ActiveStorageWidget))
		return nullptr;

	return ActiveStorageWidget->StorageComp;
}
//-----------------------------------------------------------------------------------------------------------
void UGeneralCenterWidget::UpdateCurrentStorageSlot()
{
	if (!IsValid(ActiveStorageWidget) || !IsValid(WBPInventory))
	{
		ALARM_LOG
			return;
	}
	ActiveStorageWidget->UpdateSlots();
	WBPInventory->UpdateSlots();
}
//-----------------------------------------------------------------------------------------------------------
bool UGeneralCenterWidget::IsStoreValid()
{
	if (!IsValid(WBPInventory) || !IsValid(WBPInventory->WBPStore))
		return false;

	return WBPInventory->WBPStore->GetVisibility() == ESlateVisibility::Visible ? true : false;
}
//-----------------------------------------------------------------------------------------------------------
void UGeneralCenterWidget::ShowInventory()
{
	PTR(WidgetSwitcher)->SetActiveWidget(WBPInventory);
	
	if (bIsNotFirstInvInit)
		return;

	bIsNotFirstInvInit = true;

	if (!IsValid(WBPInventory))
	{
		ALARM_LOG
		return;
	}
	
	CHECK_PTR(PlayerCharacter)
	
	WBPInventory->InitStorageWidget(PlayerCharacter->GetInventoryComponent());
	WBPInventory->WBPEquipment->InitEquipmentWidget(PlayerCharacter->GetEquipmentComponent());

	switch (StorageType)
	{
	case EStorageType::Chest:
		WBPInventory->WBPChest->InitStorageWidget(PlayerCharacter->GetChestComponent());
		WBPInventory->WBPChest->SetVisibility(ESlateVisibility::Visible);
		ActiveStorageWidget = WBPInventory->WBPChest;
		break;

	case EStorageType::TreasureInventory:
		WBPInventory->WBPEnemyInventory->InitStorageWidget(StorageComponent);
		WBPInventory->WBPEnemyInventory->SetVisibility(ESlateVisibility::Visible);
		ActiveStorageWidget = WBPInventory->WBPEnemyInventory;
		break;

	case EStorageType::Upgrade:
		WBPInventory->WBPUpgrade->InitUpgradeWidget(Cast<UUpgradeComponent>(StorageComponent));
		WBPInventory->WBPUpgrade->SetVisibility(ESlateVisibility::Visible);
		ActiveStorageWidget = WBPInventory->WBPUpgrade;
		break;

	case EStorageType::Portal:
		WBPInventory->WBPPortal->InitPortalWidget(Cast<UPortalComponent>(StorageComponent));
		WBPInventory->WBPPortal->SetVisibility(ESlateVisibility::Visible);
		ActiveStorageWidget = WBPInventory->WBPPortal;
		break;

	case EStorageType::Store:
		WBPInventory->WBPStore->InitStorageWidget(StorageComponent);
		WBPInventory->WBPStore->SetVisibility(ESlateVisibility::Visible);
		ActiveStorageWidget = WBPInventory->WBPStore;
		break;

	case EStorageType::Craft:
		WBPInventory->WBPCraft->InitStorageWidget(StorageComponent);
		WBPInventory->WBPCraft->SetVisibility(ESlateVisibility::Visible); 
		ActiveStorageWidget = WBPInventory->WBPCraft;
		break;
	case EStorageType::Inventory:
	case EStorageType::Equipment:
	case EStorageType::Quests:
		break;
	default:
		break;
	}
}
//-----------------------------------------------------------------------------------------------------------
void UGeneralCenterWidget::ShowQuests()
{
	PTR(WidgetSwitcher)->SetActiveWidget(WBPQuests);

	if (bIsNotFirstQuestsInit)
		return;

	bIsNotFirstQuestsInit = true;

	CHECK_PTR(PlayerCharacter)
	CHECK_PTR(WBPQuests)

	if(QuestGiver)
		WBPQuests->InitQuestWidget(PlayerCharacter->GetQuestComponent(), QuestGiver, MainHUD);
	else
		WBPQuests->InitQuestWidget(PlayerCharacter->GetQuestComponent(), MainHUD);
}
//-----------------------------------------------------------------------------------------------------------
void UGeneralCenterWidget::ShowInfoWidget()
{
	PTR(WidgetSwitcher)->SetActiveWidget(WBPInformation);

	if (bIsNotFirstInfoInit)
		return;

	bIsNotFirstInfoInit = true;

	CHECK_PTR(PlayerCharacter)
	CHECK_PTR(WBPInformation)

	WBPInformation->InitInformationStand();
}
//-----------------------------------------------------------------------------------------------------------
void UGeneralCenterWidget::ClickInfoButton(const FName& name)
{
	ShowInfoWidget();
	PTR(WBPInformation)->StandButtonClick(name);
}
//-----------------------------------------------------------------------------------------------------------
void UGeneralCenterWidget::InitGeneralCenterWidget(AFPSCharacter* playerCharacter, EStorageType widgetType, UStorageComponent* storageComponent, AActor* questGiverActor, UMainHUDWidget* HUD)
{
	CHECK_PTR(playerCharacter)

	PlayerCharacter = playerCharacter;
	StorageComponent = storageComponent;
	StorageType = widgetType;
	QuestGiver = questGiverActor;
	MainHUD = HUD;

	switch (StorageType)
	{
	case EStorageType::Chest:
	case EStorageType::TreasureInventory:
	case EStorageType::Upgrade:
	case EStorageType::Portal:
	case EStorageType::Inventory:
	case EStorageType::Equipment:
	case EStorageType::Store:
	case EStorageType::Craft:
		ShowInventory();
		break;
	case EStorageType::Quests:
		ShowQuests();
		break;
	default:
		break;
	}
}
//-----------------------------------------------------------------------------------------------------------
void UGeneralCenterWidget::SetItemFromIndexWidget(EStorageType type, const int32 index, const TArray<FItemInvStruct>& storage)
{
	if (!IsValid(WBPInventory))
	{
		ALARM_LOG
			return;
	}

	UWidget* widgetSlot = nullptr;
	UInventorySlotWidget* invSlot = nullptr;

	switch (type)
	{
	case EStorageType::Chest:
		CHECK_PTR(WBPInventory->WBPChest)
			CHECK_PTR(WBPInventory->WBPChest->UniformGridPanel)

			if (WBPInventory->WBPChest->UniformGridPanel->GetAllChildren().IsValidIndex(index))
				widgetSlot = WBPInventory->WBPChest->UniformGridPanel->GetAllChildren()[index];
		break;

	case EStorageType::TreasureInventory:
		CHECK_PTR(WBPInventory->WBPEnemyInventory)
			CHECK_PTR(WBPInventory->WBPEnemyInventory->UniformGridPanel)

			if (WBPInventory->WBPEnemyInventory->UniformGridPanel->GetAllChildren().IsValidIndex(index))
				widgetSlot = WBPInventory->WBPEnemyInventory->UniformGridPanel->GetAllChildren()[index];
		break;

	case EStorageType::Upgrade:
		CHECK_PTR(WBPInventory->WBPUpgrade)
			CHECK_PTR(WBPInventory->WBPUpgrade->UpgradeSlot1)
			CHECK_PTR(WBPInventory->WBPUpgrade->UpgradeSlot2)
			index == 0 ? widgetSlot = WBPInventory->WBPUpgrade->UpgradeSlot1 : widgetSlot = WBPInventory->WBPUpgrade->UpgradeSlot2;
		break;

	case EStorageType::Portal:
		CHECK_PTR(WBPInventory->WBPPortal)
			CHECK_PTR(WBPInventory->WBPPortal->PortalSlot)
			widgetSlot = WBPInventory->WBPPortal->PortalSlot;
		break;

	case EStorageType::Inventory:
		CHECK_PTR(WBPInventory->UniformGridPanel)

			if (WBPInventory->UniformGridPanel->GetAllChildren().IsValidIndex(index))
				widgetSlot = WBPInventory->UniformGridPanel->GetAllChildren()[index];
		break;

	case EStorageType::Equipment:
		CHECK_PTR(WBPInventory->WBPEquipment)
			widgetSlot = WBPInventory->WBPEquipment->SlotWidgetArray[index];
		break;

	case EStorageType::Craft:
		CHECK_PTR(WBPInventory->WBPCraft)

		if (WBPInventory->WBPCraft->UniformGridPanel->GetAllChildren().IsValidIndex(index))
			widgetSlot = WBPInventory->WBPCraft->UniformGridPanel->GetAllChildren()[index];

		break;

	}

	CHECK_PTR(widgetSlot)

		// Обновляем слот
	invSlot = Cast<UInventorySlotWidget>(widgetSlot);
	CHECK_PTR(invSlot)

	invSlot->UpdateInvSlot(storage[index].ItemDA ? storage[index].ItemDA->ItemIcon : nullptr, storage[index].ItemCount);

}
//-----------------------------------------------------------------------------------------------------------