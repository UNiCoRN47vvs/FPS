#include "Widgets/FastSlotSelector/FastSelectorIconWidget.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "Config/ItemMasterDA.h"
//-----------------------------------------------------------------------------------------------------------
void UFastSelectorIconWidget::InitSelectorIconWidget(int32 widgetIndex, int32 itemCount, UItemMasterDA* itemMasterDA)
{
	WidgetIndex = widgetIndex;
	ItemCount = itemCount;
	ItemMasterDA = itemMasterDA;

	ItemCountTB->SetText(FText::AsNumber(ItemCount));
	ItemIcon->SetBrushFromSoftTexture(ItemMasterDA->ItemIcon);
}
//-----------------------------------------------------------------------------------------------------------
FReply UFastSelectorIconWidget::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	if (InMouseEvent.GetEffectingButton() == EKeys::LeftMouseButton)
	{
		OnSelectorIconClick.ExecuteIfBound(WidgetIndex);
	}

	return Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);
}
