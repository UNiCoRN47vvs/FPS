#pragma once

#include "CoreMinimal.h"
#include "Widgets/Inventory/StorageWidget.h"
#include "Components/GridPanel.h"
#include "EquipmentWidget.generated.h"
//-----------------------------------------------------------------------------------------------------------
class UInventorySlotWidget;
class USizeBox;
//-----------------------------------------------------------------------------------------------------------
UCLASS()
class FPS_API UEquipmentWidget : public UStorageWidget
{
	GENERATED_BODY()
public:
	UFUNCTION() void InitEquipmentWidget(UStorageComponent* storageComponent);
	void GetAllInventorySlotWidgetsIn(UWidget* parentWidget, TArray<UInventorySlotWidget*>& outWidgets);
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Equipment Widget", meta = (BindWidget)) UGridPanel* GridPanel;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Equipment Widget", meta = (BindWidget)) USizeBox* SizeBox;
	
	TArray<UInventorySlotWidget*> SlotWidgetArray;
protected:
	virtual void NativeConstruct() override;
private:
};
//-----------------------------------------------------------------------------------------------------------