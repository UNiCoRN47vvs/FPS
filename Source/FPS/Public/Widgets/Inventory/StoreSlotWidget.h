#pragma once

#include "Widgets/Inventory/SlotWidget.h"
#include "Struct/ItemForSaleStruct.h"
#include "StoreSlotWidget.generated.h"
//-----------------------------------------------------------------------------------------------------------
UCLASS()
class FPS_API UStoreSlotWidget : public USlotWidget
{
	GENERATED_BODY()
public:
	TMulticastDelegate<void(FItemForSaleStruct)> OnActiveItem;
protected:
	virtual void NativeDestruct() override;
	virtual FReply NativeOnMouseButtonDown(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;
};
//-----------------------------------------------------------------------------------------------------------