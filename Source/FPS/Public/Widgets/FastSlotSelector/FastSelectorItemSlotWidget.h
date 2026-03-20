#pragma once

#include "Widgets/Inventory/SlotWidget.h"
#include "Enums/ItemType.h"
#include "FastSelectorItemSlotWidget.generated.h"
//-----------------------------------------------------------------------------------------------------------
UCLASS()
class FPS_API UFastSelectorItemSlotWidget : public USlotWidget
{
	GENERATED_BODY()
public:
	void InitSelectorSlotType(EItemType type);
protected:
	virtual void NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	virtual void NativeOnMouseLeave(const FPointerEvent& MouseEvent) override;
	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	EItemType Type;
};
//-----------------------------------------------------------------------------------------------------------