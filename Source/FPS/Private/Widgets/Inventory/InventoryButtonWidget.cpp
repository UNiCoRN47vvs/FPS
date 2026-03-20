#include "Widgets/Inventory/InventoryButtonWidget.h"
#include "Components/TextBlock.h"
//-----------------------------------------------------------------------------------------------------------
void UInventoryButtonWidget::NativePreConstruct()
{
	if(TextBlock)
		TextBlock->SetText(Text);
}
