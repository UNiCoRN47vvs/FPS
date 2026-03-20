#pragma once

#include "FPS/FPS.h"
#include "Blueprint/UserWidget.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Components/Border.h"
#include "Config/ItemGradeColorDA.h"
#include "Interfaces/InventorySlot.h"
#include "SlotWidget.generated.h"
//-----------------------------------------------------------------------------------------------------------
class AFPSPlayerController;
class UStorageComponent;
class UItemMasterDA;
class UEventBus;
//-----------------------------------------------------------------------------------------------------------
UCLASS()
class FPS_API USlotWidget : public UUserWidget, public IInventorySlot
{
	GENERATED_BODY()
public:
	virtual void UpdateInvSlot(TSoftObjectPtr<UTexture2D> icon, int32 count) override;
	void UpdateInvSlot(TSoftObjectPtr<UTexture2D> icon, int32 count, UItemMasterDA* itemDataAsset);
	virtual void UpdateInvSlot();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Slot Widget") int32 Index;
	UPROPERTY(BlueprintReadOnly, Category = "Slot Widget", meta = (BindWidget)) UImage* Image;
	UPROPERTY(BlueprintReadOnly, Category = "Slot Widget", meta = (BindWidget)) UTextBlock* ItemCountTB;
	UPROPERTY(BlueprintReadOnly, Category = "Slot Widget", meta = (BindWidget)) UTextBlock* ItemLevelTB;
	UPROPERTY(BlueprintReadOnly, Category = "Slot Widget", meta = (BindWidget)) UTextBlock* PlusTB;
	UPROPERTY(BlueprintReadOnly, Category = "Slot Widget", meta = (BindWidget)) UBorder* ItemGradeBorder;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Slot Widget") FSlateBrush BorderBrush;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Slot Widget") UItemGradeColorDA* ItemGradeColorDA;
	UPROPERTY() UStorageComponent* StorageComponent;
protected:
	virtual void NativeConstruct() override;
	virtual void NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	virtual void NativeOnMouseLeave(const FPointerEvent& MouseEvent) override;
	void UpdateInvSlotSubFunc1(TSoftObjectPtr<UTexture2D> icon, int32 count);
	void UpdateInvSlotSubFunc2();

	UPROPERTY() UItemMasterDA* ItemDA;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Slot Widget") TSoftObjectPtr<UTexture2D> DefaultImage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Slot Widget") TSoftObjectPtr<UTexture2D> ImageTexture2D;
	UPROPERTY() AFPSPlayerController* PlayerController;

private:
};
//-----------------------------------------------------------------------------------------------------------