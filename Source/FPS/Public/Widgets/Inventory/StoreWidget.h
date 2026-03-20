#pragma once

#include "Widgets/Inventory/ChestWidget.h"
#include "Struct/ItemForSaleStruct.h"
#include "StoreWidget.generated.h"
//-----------------------------------------------------------------------------------------------------------
class UInventoryButtonWidget;
class USlotWidget;
class UStoreItemWidget;
class UUniformGridPanel;
class UVerticalBox;
class UNPCStorageComponent;
class UInventoryComponent;
//-----------------------------------------------------------------------------------------------------------
UCLASS()
class FPS_API UStoreWidget : public UChestWidget
{
	GENERATED_BODY()
public:
	virtual void InitStorageWidget(UStorageComponent* StorageComponent) override;

	UPROPERTY(BlueprintReadOnly, Category = "Store Widget", meta = (BindWidget)) UInventoryButtonWidget* ResreshButton;
	UPROPERTY(BlueprintReadOnly, Category = "Store Widget", meta = (BindWidget)) UVerticalBox* StoreVB;

protected:
	FItemForSaleStruct CurrentActiveItem;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Store Widget") USoundWave* RefreshSound;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Store Widget") TSubclassOf<USlotWidget> RecipeSlot;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Store Widget") TSubclassOf<UStoreItemWidget> StoreItemWidgetClass;
private:
	void Refresh();
	UFUNCTION() void RefreshStore();

	UPROPERTY() UNPCStorageComponent* NPCStorageComponent;
	UPROPERTY() UInventoryComponent* InventoryComponent;
};
//-----------------------------------------------------------------------------------------------------------