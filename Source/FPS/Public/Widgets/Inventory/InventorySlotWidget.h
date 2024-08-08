#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Interfaces/InventorySlot.h"
#include "InventorySlotWidget.generated.h"
//-----------------------------------------------------------------------------------------------------------
UCLASS()
class FPS_API UInventorySlotWidget : public UUserWidget, public IInventorySlot
{
	GENERATED_BODY()
public:
	virtual void UpdateInvSlot(TSoftObjectPtr<UTexture2D> Icon, int Count) override;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Inventory Slot Widget") int Index;
	UPROPERTY(BlueprintReadOnly, Category = "Inventory Slot Widget", meta = (BindWidget)) UImage* Image;
	UPROPERTY(BlueprintReadOnly, Category = "Inventory Slot Widget", meta = (BindWidget)) UTextBlock* ItemCountTB;
protected:
	virtual void NativeConstruct() override;
	virtual void NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation) override;
	virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventor Slot Widget") TSoftObjectPtr<UTexture2D> DefaultImage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventor Slot Widget") TSoftObjectPtr<UTexture2D> ImageTexture2D;
private:
	void DragDropFunc(bool bIsDrop);

};
//-----------------------------------------------------------------------------------------------------------