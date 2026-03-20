#include "Widgets/MainHUD/MainHUDWidget.h"
#include "Components/SizeBox.h"
#include "Components/TextBlock.h"
#include "Components/VerticalBox.h"
#include "Components/Button.h"
#include "SubSystem/EventBus.h"
#include "FPS/FPSCharacter.h"
#include "FPS/FPSPlayerController.h"
#include "ActorComponents/Equipment/EquipmentComponent.h"
#include "ActorComponents/Quest/PlayerQuestComponent.h"
#include "Widgets/ProgressBar/ProgressBarWidget.h"
#include "Widgets/Inventory/InventoryWidget.h"
#include "Widgets/Equipment/EquipmentWidget.h"
#include "Widgets/Inventory/StoreWidget.h"
#include "Widgets/ElementalEffects/ElementalEffects.h"
#include "Widgets/MainHUD/WaveEnemyCountWidget.h"
#include "Widgets/MainMenu/EscapeMenuWidget.h"
#include "Widgets/MainHUD/FramePerSecondWidget.h"
#include "Widgets/Dialog/DialogWidget.h"
#include "Widgets/Quest/PopUpQuestGoalWidget.h"
#include "Widgets/GeneralCenterWidget/GeneralCenterWidget.h"
#include "Config/ItemMasterDA.h"
//-----------------------------------------------------------------------------------------------------------
void UMainHUDWidget::NativeConstruct()
{
	Super::NativeConstruct();
	bool bIsShowFPS;

	PlayerCharacter = Cast<AFPSCharacter>(GetOwningPlayer()->GetPawn());
	if (PlayerCharacter)
	{
		UPlayerStateComponent* stateComponent = PlayerCharacter->GetPlayerStateComponent();
		UEquipmentComponent* equipmentComponent = PlayerCharacter->GetEquipmentComponent();
		UInventoryWidget* inventoryWidget = CreateWidget<UInventoryWidget>(GetWorld(), InventoryWidget);
		if (stateComponent)
			stateComponent->OnChangeState.AddUObject(this, &UMainHUDWidget::UpdateProgressBar);
		else
			ALARM_LOG

		if (inventoryWidget && equipmentComponent)
		{
			inventoryWidget->WBPEquipment->GetAllInventorySlotWidgetsIn(inventoryWidget->WBPEquipment->SizeBox, inventoryWidget->WBPEquipment->SlotWidgetArray);
			equipmentComponent->InitEquipmentSlots(inventoryWidget->WBPEquipment->SlotWidgetArray);
			inventoryWidget->RemoveFromParent();
		}

		WBPElementalEffects->InitParams(stateComponent);
	}
	else
		ALARM_LOG

	GConfig->GetBool(TEXT("/Script/FPS.FPSGameInstance"), TEXT("bShowFPS"), bIsShowFPS, GGameIni);

	ShowHideFrameRate(bIsShowFPS);

	CHECK_PTR(PlayerCharacter->GetQuestComponent())
	PlayerCharacter->GetQuestComponent()->OnQuestGoal.BindUObject(this, &UMainHUDWidget::QuestGoal);
	
	UEventBus::OnCreateDialogWidget.BindUObject(this, &UMainHUDWidget::CreateDialogWidget);
	UEventBus::OnTriggerInteractWidget.BindUObject(this, &UMainHUDWidget::TriggerInteractWidget);
	UEventBus::OnDragDropOperation.BindUObject(this, &UMainHUDWidget::DragDropOperation);
	UEventBus::OnFastPickUp.BindUObject(this, &UMainHUDWidget::FastPickUpPopUp);
	UEventBus::OnHitEnemyWidgetAnim.BindUObject(this, &UMainHUDWidget::PlayHitEnemyAnimation);
	UEventBus::OnShowFPS.BindUObject(this, &UMainHUDWidget::ShowHideFrameRate);
	UEventBus::OnGetDragStorage.BindUObject(this, &UMainHUDWidget::GetDragStorage);
	UEventBus::OnGetDragIndex.BindUObject(this, &UMainHUDWidget::GetDragIndex);
	UEventBus::OnGetKeyInfo.BindUObject(this, &UMainHUDWidget::GetKeyInfo);

}
//-----------------------------------------------------------------------------------------------------------
void UMainHUDWidget::NativeDestruct()
{
	Super::NativeDestruct();

	UEventBus::OnCreateDialogWidget.Unbind();
	UEventBus::OnTriggerInteractWidget.Unbind();
	UEventBus::OnDragDropOperation.Unbind();
	UEventBus::OnFastPickUp.Unbind();
	UEventBus::OnHitEnemyWidgetAnim.Unbind();
	UEventBus::OnShowFPS.Unbind();
	UEventBus::OnGetDragStorage.Unbind();
	UEventBus::OnGetDragIndex.Unbind();
	UEventBus::OnGetKeyInfo.Unbind();
}
//-----------------------------------------------------------------------------------------------------------
void UMainHUDWidget::QuestGoal(FQuest questStruct)
{
	CHECK_PTR(questStruct.QuestMasterDA)

	UPopUpQuestGoalWidget* popUpWidget;

	popUpWidget = CreateWidget<UPopUpQuestGoalWidget>(this, PopUpQuestWidget);
	CHECK_PTR(popUpWidget)

	PopUpQuestBox->AddChild(popUpWidget);
	popUpWidget->InitPopUpQuestGoal(questStruct);
}
//-----------------------------------------------------------------------------------------------------------
void UMainHUDWidget::UpdateProgressBar(EStateName stateName, float currentValue, float maxValue)
{
	switch (stateName)
	{
	case EStateName::Health:
	case EStateName::HealthMax:
		WBPHealth->SetValueProgressBar(currentValue, maxValue);
		break;
	
	case EStateName::Stamina:
	case EStateName::StaminaMax:
		WBPStamina->SetValueProgressBar(currentValue, maxValue);
		break;

	case EStateName::Mana:
	case EStateName::ManaMax:
		WBPMana->SetValueProgressBar(currentValue, maxValue);
		break;

	default:
		break;
	}
}
//-----------------------------------------------------------------------------------------------------------
//Getter
UStorageComponent* UMainHUDWidget::GetDragStorage()
{
	return DragStorage;
}
int UMainHUDWidget::GetDragIndex() const
{
	return DragIndex;
}
UStorageComponent* UMainHUDWidget::GetCurrentActiveStorage()
{
	if (!IsValid(WBPGeneralCenter))
		return nullptr;

	return WBPGeneralCenter->GetCurrentActiveStorage();
}
const TMap<FKey, FText>& UMainHUDWidget::GetKeyInfo()
{
	return KeyInfo;
}
void UMainHUDWidget::UpdateCurrentStorageSlot()
{
	if (!IsValid(WBPGeneralCenter) )
	{
		ALARM_LOG
			return;
	}

	WBPGeneralCenter->UpdateCurrentStorageSlot();
}
//-----------------------------------------------------------------------------------------------------------
void UMainHUDWidget::DragDropOperation(UStorageComponent* storageComponent, int32 index, bool bIsDrop)
{
	if (bIsDrop)
	{
		bool borosBool1 = false;
		bool borosBool2 = false;

		DropStorage = storageComponent;
		DropIndex = index;
		if (DragStorage && DropStorage && !(DragStorage == DropStorage && DragIndex == DropIndex)) // Если предметы перемещаются между разными слотами, выполняем обмен
		{
			int32 count = 0;
			TArray<FItemInvStruct> dragItemStorage = DragStorage->GetStorage();
			TArray<FItemInvStruct> dropItemStorage = DropStorage->GetStorage();

			if (DragStorage->GetStorage()[DragIndex].bOccupied && DropStorage->GetStorage()[DropIndex].bOccupied)
			{
				CHECK_PTR(dragItemStorage[DragIndex].ItemDA)
				CHECK_PTR(dropItemStorage[DropIndex].ItemDA)

				borosBool1 = dragItemStorage[DragIndex].ItemDA->ItemName == dropItemStorage[DropIndex].ItemDA->ItemName;
				borosBool2 = dragItemStorage[DragIndex].ItemDA->ItemGrade == dropItemStorage[DropIndex].ItemDA->ItemGrade;

				if (borosBool1&& borosBool2) // Если предметы одинаковы, складываем их в один слот
				{
					count = dropItemStorage[DropIndex].ItemCount + dragItemStorage[DragIndex].ItemCount;
					if (dropItemStorage[DropIndex].ItemDA && count > dropItemStorage[DropIndex].ItemDA->ItemCountMax)
					{
						dragItemStorage[DragIndex].ItemCount = dropItemStorage[DropIndex].ItemDA->ItemCountMax;
						dropItemStorage[DropIndex].ItemCount = count - dropItemStorage[DropIndex].ItemDA->ItemCountMax;
					}
					else
					{
						dragItemStorage[DragIndex].ItemCount = count;
						dropItemStorage[DropIndex] = FItemInvStruct{};
					}
				}
			}

			// Обновляем слоты инвентаря
			DragStorage->SetItemFromIndex(dropItemStorage[DropIndex], DragStorage->CurrentActiveInvTab, DragIndex);
			DropStorage->SetItemFromIndex(dragItemStorage[DragIndex], DropStorage->CurrentActiveInvTab, DropIndex);
		}
	}
	else
	{
		DragStorage = storageComponent;
		DragIndex = index;
	}
}
//-----------------------------------------------------------------------------------------------------------
void UMainHUDWidget::CreateWidgetByType(EStorageType widgetType, UStorageComponent* storageComponent, AActor* questGiverActor)
{
	if (IsValid(WBPGeneralCenter))
	{
		UEventBus::OnSaveGame.ExecuteIfBound();
		UEventBus::OnGeneralWidgetClose.Broadcast();

		WBPGeneralCenter->RemoveFromParent();
		WBPGeneralCenter = nullptr;
		OnSetWidgetInputMode.ExecuteIfBound(false);
		return;
	}
	
	OnSetWidgetInputMode.ExecuteIfBound(true);

	WBPGeneralCenter = CreateWidget<UGeneralCenterWidget>(this, GeneralCenterWidget);
	
	PTR(WBPGeneralCenter)->AddToViewport(999999);
	CHECK_CAST(PlayerCharacter, AFPSCharacter, GetOwningPlayer()->GetPawn())

	if (IsValid(WBPDialog))
	{
		WBPDialog->RemoveFromParent();
		WBPDialog = nullptr;
	}

	WBPGeneralCenter->InitGeneralCenterWidget(PlayerCharacter, widgetType, storageComponent, questGiverActor);
	WBPGeneralCenter->CloseButton->OnClicked.AddDynamic(this, &UMainHUDWidget::CloseGeneral);

	UEventBus::OnWeightCalculation.ExecuteIfBound();	
}
//-----------------------------------------------------------------------------------------------------------
void UMainHUDWidget::CloseGeneral()
{
	CreateWidgetByType(EStorageType::Quests);
}
//-----------------------------------------------------------------------------------------------------------
void UMainHUDWidget::FastPickUpPopUp(const FItemInvStruct& itemStruct)
{
	CHECK_PTR(itemStruct.ItemDA)

	UPopUpMasterWidget* popUpWidget;

	popUpWidget = CreateWidget<UPopUpMasterWidget>(this, PopUpFastPickUpWidget);
	CHECK_PTR(popUpWidget)

	PopUpFastPickUpBox->AddChild(popUpWidget);
	popUpWidget->InitPopUp(FText::FromName(itemStruct.ItemDA->ItemName), itemStruct.ItemCount, itemStruct.ItemDA->ItemIcon);
}
//-----------------------------------------------------------------------------------------------------------
void UMainHUDWidget::ShowHideDeathBorder(bool bIsShow)
{
	if (!bIsShow)
		DeathBorder->SetVisibility(ESlateVisibility::Collapsed);
	else
	{
		WBPWaveEnemyCount->SetVisibility(ESlateVisibility::Collapsed);
		DeathBorder->SetVisibility(ESlateVisibility::Visible);
	}
}
//-----------------------------------------------------------------------------------------------------------
void UMainHUDWidget::CreateRemoveEscapeMenu(bool bIsCreate)
{
	CHECK_CAST(PlayerController, AFPSPlayerController, GetOwningPlayer())

	if (bIsCreate)
	{
		WBPEscapeMenu = CreateWidget<UEscapeMenuWidget>(GetWorld(), EscapeMenuWidget);
		if (!IsValid(WBPEscapeMenu))
		{
			ALARM_LOG
			return;
		}

		CenterVerticalBox->AddChild(WBPEscapeMenu);
	}
	else
	{
		WBPEscapeMenu->RemoveFromParent();
		WBPEscapeMenu = nullptr;
	}

	PlayerController->SetWidgetInputMode(bIsCreate);
}
//-----------------------------------------------------------------------------------------------------------
void UMainHUDWidget::PlayHitEnemyAnimation()
{
	PlayAnimation(HitToEnemyAnimation);
}
//-----------------------------------------------------------------------------------------------------------
void UMainHUDWidget::TriggerInteractWidget(bool bIsShow, FText& text)
{
	if (!bIsShow)
		InteractWidgetTB->SetVisibility(ESlateVisibility::Collapsed);
	else
	{
		InteractWidgetTB->SetVisibility(ESlateVisibility::Visible);
		InteractWidgetTB->SetText(text);
	}
}
//-----------------------------------------------------------------------------------------------------------
void UMainHUDWidget::ShowHideFrameRate(bool bIsShow)
{
	if (bIsShow)
	{
		if (IsValid(WBPFrameRate))
			return;

		WBPFrameRate = CreateWidget<UFramePerSecondWidget>(GetWorld(), FrameWidget);
		if (!IsValid(WBPFrameRate))
		{
			ALARM_LOG
			return;
		}

		WBPFrameRate->AddToViewport();
	}
	else
	{
		if (IsValid(WBPFrameRate))
		{
			WBPFrameRate->RemoveFromParent();
			WBPFrameRate = nullptr;
		}
	}

}
//-----------------------------------------------------------------------------------------------------------
void UMainHUDWidget::CreateDialogWidget(UStorageComponent* storageComp)
{
	if (IsValid(WBPDialog))
	{
		WBPDialog->RemoveFromParent();
		WBPDialog = nullptr;
		OnSetWidgetInputMode.ExecuteIfBound(false);
		return;
	}

	CHECK_PTR(DialogWidget)

	WBPDialog = CreateWidget<UDialogWidget>(this, DialogWidget);

	CHECK_PTR(WBPDialog)
	FText text = {};
	TriggerInteractWidget(false, text);

	WBPDialog->InitDialogWidget(storageComp, this);
	CenterVerticalBox->AddChild(WBPDialog);

	OnSetWidgetInputMode.ExecuteIfBound(true);
}
//-----------------------------------------------------------------------------------------------------------
bool UMainHUDWidget::IsStoreValid()
{
	if (!IsValid(WBPGeneralCenter))
		return false;

	return WBPGeneralCenter->IsStoreValid();
}
//-----------------------------------------------------------------------------------------------------------
void UMainHUDWidget::UpdateTimeCount(int32 Count)
{
	if(WBPWaveEnemyCount->GetVisibility() != ESlateVisibility::Visible)
		WBPWaveEnemyCount->SetVisibility(ESlateVisibility::Visible);

	WBPWaveEnemyCount->UpdateTimeCount(Count);
}
void UMainHUDWidget::UpdateWaveCount(int32 Count)
{
	WBPWaveEnemyCount->UpdateWaveCount(Count);
}
void UMainHUDWidget::UpdateEnemyCount(int32 Count)
{
	WBPWaveEnemyCount->UpdateEnemyCount(Count);
}
//-----------------------------------------------------------------------------------------------------------
void UMainHUDWidget::HealthHitReaction()
{
	if(HealthHitAnimation)
		PlayAnimation(HealthHitAnimation);
}
//-----------------------------------------------------------------------------------------------------------