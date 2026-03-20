#pragma once

#include "Widgets/Inventory/SlotWidget.h"
#include "Enums/ItemType.h"
#include "InventorySlotWidget.generated.h"
//-----------------------------------------------------------------------------------------------------------
class USizeBox;
class UPopupActionMenuWidget;
class UMetaSoundSource;
//-----------------------------------------------------------------------------------------------------------
UCLASS()
class FPS_API UInventorySlotWidget : public USlotWidget
{
	GENERATED_BODY()
public:
	void PlaySlotAnimation(bool bIsPlay);

	UPROPERTY(BlueprintReadOnly, Category = "I_S_W", meta = (BindWidget)) USizeBox* SizeBox;
	UPROPERTY(BlueprintReadOnly, Category = "I_S_W", meta = (BindWidgetAnim), Transient) UWidgetAnimation* BacklightAnimation;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "I_S_W") EItemType SlotType;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "I_S_W") TSubclassOf<UPopupActionMenuWidget> WBPPopupMenu;

	uint8 bIsSlotBlock : 1;
protected:
	virtual void NativeConstruct() override;
	virtual void NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation) override;
	virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;
	virtual FReply NativeOnMouseButtonDown(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;

	UFUNCTION() void UpdateSlot();
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "I_S_W") UMetaSoundSource* DropSound;
private:


};
//-----------------------------------------------------------------------------------------------------------