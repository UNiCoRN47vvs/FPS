#include "Widgets/FastSlotSelector/FastSelectorItemSlotWidget.h"
#include "SubSystem/EventBus.h"
//-----------------------------------------------------------------------------------------------------------
void UFastSelectorItemSlotWidget::InitSelectorSlotType(EItemType type)
{
	Type = type;
}
//-----------------------------------------------------------------------------------------------------------
void UFastSelectorItemSlotWidget::NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
}
//-----------------------------------------------------------------------------------------------------------
void UFastSelectorItemSlotWidget::NativeOnMouseLeave(const FPointerEvent& MouseEvent)
{
}
//-----------------------------------------------------------------------------------------------------------
FReply UFastSelectorItemSlotWidget::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	if (InMouseEvent.GetEffectingButton() == EKeys::LeftMouseButton)
	{
		switch (Type)
		{
		case EItemType::Potion:
			UEventBus::OnSelectorPotion.ExecuteIfBound(ItemDA);
			break;

		case EItemType::ScrollSkill:
			UEventBus::OnSelectorScroll.ExecuteIfBound(ItemDA);
			break;
		}
	}

	return Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);
}
//-----------------------------------------------------------------------------------------------------------