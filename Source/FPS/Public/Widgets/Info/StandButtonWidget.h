#pragma once

#include "Widgets/Inventory/InventoryButtonWidget.h"
#include "StandButtonWidget.generated.h"
//-----------------------------------------------------------------------------------------------------------
UCLASS()
class FPS_API UStandButtonWidget : public UInventoryButtonWidget
{
	GENERATED_BODY()

public:
	void InitStandButton(const FName& name);
	TDelegate<void(const FName&)> OnStandButtonClick;

protected:
	UFUNCTION() void StandButtonClick();
	FName Name;
};
//-----------------------------------------------------------------------------------------------------------