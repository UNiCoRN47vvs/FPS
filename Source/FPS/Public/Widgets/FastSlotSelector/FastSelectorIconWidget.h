#pragma once

#include "FPS/FPS.h"
#include "Blueprint/UserWidget.h"
#include "FastSelectorIconWidget.generated.h"
//-----------------------------------------------------------------------------------------------------------
class UTextBlock;
class UImage;
class UItemMasterDA;
//-----------------------------------------------------------------------------------------------------------
UCLASS()
class FPS_API UFastSelectorIconWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	void InitSelectorIconWidget(int32 widgetIndex, int32 itemCount, UItemMasterDA* itemMasterDA);
	UPROPERTY(BlueprintReadOnly, Category = "F_S_I_W", meta = (BindWidget)) UTextBlock* ItemCountTB;
	UPROPERTY(BlueprintReadOnly, Category = "F_S_I_W", meta = (BindWidget)) UImage* ItemIcon;

	TDelegate<void(int32)> OnSelectorIconClick;

	int32 WidgetIndex;
	int32 ItemCount;
	UPROPERTY() UItemMasterDA* ItemMasterDA;
protected:
	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
};
//-----------------------------------------------------------------------------------------------------------