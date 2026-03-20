#pragma once

#include "Widgets/Inventory/GenegalStorageWidget.h"
#include "PortalWidget.generated.h"
//-----------------------------------------------------------------------------------------------------------
class UInventorySlotWidget;
class UButton;
class UPortalComponent;
class UWorldRuler;
//-----------------------------------------------------------------------------------------------------------
UCLASS()
class FPS_API UPortalWidget : public UGenegalStorageWidget
{
	GENERATED_BODY()
public:
	virtual void UpdateSlots() override;
	void InitPortalWidget(UPortalComponent* storageComponent);
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "FPS Game Mode") UDataTable* DTPortalStones;
	UPROPERTY(BlueprintReadOnly, Category = "Portal Widget", meta = (BindWidget)) UInventorySlotWidget* PortalSlot;
	UPROPERTY(BlueprintReadOnly, Category = "Portal Widget", meta = (BindWidget)) UButton* PortalButton;
	UPROPERTY(BlueprintReadOnly, Category = "Portal Widget", meta = (BindWidget)) UButton* FreePortalButton;
protected:
	UFUNCTION() void CheckAndOpenPortal();
	UFUNCTION() void OpenFreePortal();
	void RemoveCurrentDungeonPortal(UWorldRuler* worldRuler,const FName& functionName);
private:
	UPortalComponent* PortalComponent;
};
