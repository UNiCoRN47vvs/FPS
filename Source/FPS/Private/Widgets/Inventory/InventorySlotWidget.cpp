#include "Widgets/Inventory/InventorySlotWidget.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "SubSystem/EventBus.h"
#include "FPS/FPSPlayerController.h"
#include "Widgets/Inventory/PopupActionMenuWidget.h"
#include "ActorComponents/StorageComponent.h"
//-----------------------------------------------------------------------------------------------------------
void UInventorySlotWidget::NativeConstruct()
{
	Super::NativeConstruct();
	//UpdateInvSlot(DefaultImage, 0);

	FTimerHandle timerHandle = {};

	GetWorld()->GetTimerManager().SetTimer(timerHandle, [this]()
		{
			if (StorageComponent && IsValid(this))
				StorageComponent->OnPickUpItem.AddDynamic(this, &UInventorySlotWidget::UpdateSlot);
		}, 0.025, false);
}
//-----------------------------------------------------------------------------------------------------------
void UInventorySlotWidget::UpdateSlot()
{
	UpdateInvSlot();
}
//-----------------------------------------------------------------------------------------------------------
void UInventorySlotWidget::PlaySlotAnimation(bool bIsPlay)
{
	if(bIsPlay)
		PlayAnimationTimeRange(BacklightAnimation, 0.0, 0.0, 0);
	else
		StopAnimation(BacklightAnimation);
}
//-----------------------------------------------------------------------------------------------------------
void UInventorySlotWidget::NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation)
{
	if (StorageComponent && !StorageComponent->GetStorage()[Index].bOccupied || bIsSlotBlock)
		return;

	Super::NativeOnDragDetected(InGeometry, InMouseEvent, OutOperation);

	if (StorageComponent->GetStorage()[Index].ItemDA)
		UEventBus::OnPlaySlotAnimationWidget.ExecuteIfBound(true, StorageComponent->GetStorage()[Index].ItemDA->ItemType);
	
	UEventBus::OnDragDropOperation.ExecuteIfBound(StorageComponent, Index, false);
}
//-----------------------------------------------------------------------------------------------------------
bool UInventorySlotWidget::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	Super::NativeOnDrop(InGeometry, InDragDropEvent, InOperation);

	int32 dragIndex = 0;
	UStorageComponent* dragComponent = nullptr;

	if (!UEventBus::OnGetDragStorage.IsBound() || !UEventBus::OnGetDragIndex.IsBound())
		return false;

	dragComponent = UEventBus::OnGetDragStorage.Execute();
	dragIndex = UEventBus::OnGetDragIndex.Execute();

	UEventBus::OnPlaySlotAnimationWidget.ExecuteIfBound(false, EItemType::All);

	if (!dragComponent)
	{
		ALARM_LOG
		return false;
	}

	const TArray<FItemInvStruct>& dragStorage = dragComponent->GetStorage();

	if (SlotType == EItemType::All || dragStorage[dragIndex].ItemDA->ItemType == SlotType)
		UEventBus::OnDragDropOperation.ExecuteIfBound(StorageComponent, Index, true);
	

	return false;
}
//-----------------------------------------------------------------------------------------------------------
FReply UInventorySlotWidget::NativeOnMouseButtonDown(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent)
{
	if (!PlayerController)
	{
		PlayerController = Cast<AFPSPlayerController>(this->GetOwningPlayer());
		if (!PlayerController )
		{
			ALARM_LOG
			return Super::NativeOnMouseButtonDown(MyGeometry, MouseEvent);
		}
	}

	if (MouseEvent.GetEffectingButton() == EKeys::LeftMouseButton && PlayerController->bIsFastDrag)
	{
		if (!StorageComponent)
			return Super::NativeOnMouseButtonDown(MyGeometry, MouseEvent);

		switch (StorageComponent->GetStorageType())
		{
		case EStorageType::Equipment:
			return Super::NativeOnMouseButtonDown(MyGeometry, MouseEvent);
			break;
		default:
			break;
		}

		UGameplayStatics::SpawnSound2D(GetWorld(), DropSound);
		StorageComponent->ApplyFastDrop(PlayerController, Index, this);
	}

	if (MouseEvent.GetEffectingButton() == EKeys::RightMouseButton && StorageComponent->GetStorage()[Index].bOccupied)
	{
		if (PlayerController->PopupMenu.IsValid())
		{
			PlayerController->PopupMenu->RemoveFromParent();
			PlayerController->PopupMenu = nullptr;
		}
		
		float mouseX = 0.0;
		float mouseY = 0.0;
		UPopupActionMenuWidget* popupMenu = CreateWidget<UPopupActionMenuWidget>(PlayerController, WBPPopupMenu);
		if (!popupMenu)
		{
			ALARM_LOG
			return Super::NativeOnMouseButtonDown(MyGeometry, MouseEvent);
		}

		popupMenu->SetData(Index, StorageComponent, PlayerController);
		popupMenu->AddToViewport(9999999);
		PlayerController->PopupMenu = popupMenu;


		if (PlayerController->GetMousePosition(mouseX, mouseY))
			popupMenu->SetPositionInViewport(FVector2D(mouseX, mouseY), false);
	}
	return Super::NativeOnMouseButtonDown(MyGeometry, MouseEvent);
}