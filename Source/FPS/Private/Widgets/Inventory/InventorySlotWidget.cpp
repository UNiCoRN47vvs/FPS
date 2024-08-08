#include "Widgets/Inventory/InventorySlotWidget.h"
#include "Interfaces/StorageInterface.h"
#include "Interfaces/DragDropInterface.h"
#include "ActorComponents/Inventory/InventoryComponent.h" //Изменить когда будет общий родитель у инвентаря и сундука!
//-----------------------------------------------------------------------------------------------------------
void UInventorySlotWidget::NativeConstruct()
{
	Super::NativeConstruct();
	UTexture2D* LocalDefaultImage = DefaultImage.LoadSynchronous();
	if(LocalDefaultImage)
		Image->SetBrushFromTexture(LocalDefaultImage);
}
//-----------------------------------------------------------------------------------------------------------
void UInventorySlotWidget::UpdateInvSlot(TSoftObjectPtr<UTexture2D> Icon, int Count)
{
	ImageTexture2D = Icon;
	if (Count > 0) 
	{
		UTexture2D* LocalIconImage = Icon.LoadSynchronous();
		if (LocalIconImage)
		{
			Image->SetBrushFromTexture(LocalIconImage);
			ItemCountTB->SetText(FText::AsNumber(Count));
		}
	}
	else
	{
		UTexture2D* LocalDefaultImage = DefaultImage.LoadSynchronous();
		if (LocalDefaultImage)
		{
			Image->SetBrushFromTexture(LocalDefaultImage);
			ItemCountTB->SetText(FText::FromString(TEXT("")));
		}
	}
}
//-----------------------------------------------------------------------------------------------------------
void UInventorySlotWidget::NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation)
{
	Super::NativeOnDragDetected(InGeometry, InMouseEvent, OutOperation);
	DragDropFunc(false);
}
//-----------------------------------------------------------------------------------------------------------
bool UInventorySlotWidget::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	Super::NativeOnDrop(InGeometry, InDragDropEvent, InOperation);
	DragDropFunc(true);
	return false;
}
//-----------------------------------------------------------------------------------------------------------
void UInventorySlotWidget::DragDropFunc(bool bIsDrop)
{
	IStorageInterface* LocalStorageInterface = Cast<IStorageInterface>(this->GetRootWidget());
	if (LocalStorageInterface)
	{
		UInventoryComponent* LocalStorageComponent = Cast<UInventoryComponent>(LocalStorageInterface->GetStorageComponent());
		if (LocalStorageComponent)
		{
			IDragDropInterface* LocalDragDropInterface = Cast<IDragDropInterface>(this->GetOwningPlayer());
			if (LocalDragDropInterface)
			{
				LocalDragDropInterface->DragDropOperation(LocalStorageComponent, Index, bIsDrop);
				return;
			}
		}
	}
	return GEngine->AddOnScreenDebugMessage(0, 5, FColor::Cyan, FString(TEXT("FPSCharacter, LocalStorageInterface or LocalStorageComponent or LocalDragDropInterface = nullptr!")));
}
