#pragma once

#include "Widgets/Inventory/StorageWidget.h"
#include "Enums/StorageType.h"
#include "Enums/ItemType.h"
#include "InventoryWidget.generated.h"
//-----------------------------------------------------------------------------------------------------------
class UTextBlock;
class UEquipmentWidget;
class UUpgradeWidget;
class UPortalWidget;
class UChestWidget;
class UInformationWidget;
class UItemMasterDA;
class UStoreWidget;
class UEventBus;
class UInventoryComponent;
class USortButtonWidget;
class UCraftWidget;
struct FCurrency;
struct FItemInvStruct;
//-----------------------------------------------------------------------------------------------------------
UCLASS()
class FPS_API UInventoryWidget : public UStorageWidget
{
	GENERATED_BODY()
public:
	virtual void InitStorageWidget(UStorageComponent* storageComponent) override;
	void UpdateWeight(const float weight);
	void UpdateCurrency();
	UFUNCTION() void PlaySlotAnimation(bool bIsPlay, EItemType itemType);

	UPROPERTY(BlueprintReadOnly, Category = "I_W", meta = (BindWidget)) USortButtonWidget* ButtonSortItemType;
	UPROPERTY(BlueprintReadOnly, Category = "I_W", meta = (BindWidget)) USortButtonWidget* ButtonSortItemGrade;
	UPROPERTY(BlueprintReadOnly, Category = "I_W", meta = (BindWidget)) USortButtonWidget* ButtonSortItemName;
	UPROPERTY(BlueprintReadOnly, Category = "I_W", meta = (BindWidget)) UTextBlock* SulfurTB;
	UPROPERTY(BlueprintReadOnly, Category = "I_W", meta = (BindWidget)) UTextBlock* WeightTB;
	UPROPERTY(BlueprintReadOnly, Category = "I_W", meta = (BindWidget)) UEquipmentWidget* WBPEquipment;

	UPROPERTY(BlueprintReadOnly, Category = "I_W", meta = (BindWidget)) UUpgradeWidget* WBPUpgrade;
	UPROPERTY(BlueprintReadOnly, Category = "I_W", meta = (BindWidget)) UPortalWidget* WBPPortal;
	UPROPERTY(BlueprintReadOnly, Category = "I_W", meta = (BindWidget)) UChestWidget* WBPChest;
	UPROPERTY(BlueprintReadOnly, Category = "I_W", meta = (BindWidget)) UChestWidget* WBPEnemyInventory;
	UPROPERTY(BlueprintReadOnly, Category = "I_W", meta = (BindWidget)) UStoreWidget* WBPStore;
	UPROPERTY(BlueprintReadOnly, Category = "I_W", meta = (BindWidget)) UCraftWidget* WBPCraft;
	
protected:
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;
	UPROPERTY() UStorageComponent* StorageComponent;
private:
	UFUNCTION() void UpdateWidgetInfo();

	UPROPERTY() UInventoryComponent* InventoryComponent;
};
//-----------------------------------------------------------------------------------------------------------