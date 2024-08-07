#include "Widgets/Inventory/InventorySlotWidget.h"
//-----------------------------------------------------------------------------------------------------------
void UInventorySlotWidget::NativeConstruct()
{
	Super::NativeConstruct();
	UTexture2D* LocalDefaultImage = DefaultImage.LoadSynchronous();
	if(LocalDefaultImage)
		Image->SetBrushFromTexture(LocalDefaultImage);
}
