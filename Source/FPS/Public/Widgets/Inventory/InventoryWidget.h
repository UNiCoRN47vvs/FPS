#pragma once

#include "Widgets/Inventory/StorageWidget.h"
#include "InventoryWidget.generated.h"
//-----------------------------------------------------------------------------------------------------------
UCLASS()
class FPS_API UInventoryWidget : public UStorageWidget
{
	GENERATED_BODY()
public:

	virtual UStorageComponent* GetStorageComponent() override;
	
protected:
	virtual void NativeConstruct() override;
private:
	UFUNCTION() void HideInventory();
};
//-----------------------------------------------------------------------------------------------------------
