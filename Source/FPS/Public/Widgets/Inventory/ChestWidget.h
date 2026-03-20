#pragma once

#include "Widgets/Inventory/StorageWidget.h"
#include "ChestWidget.generated.h"
//-----------------------------------------------------------------------------------------------------------
class UScrollBox;
class UStorageTabButtonWidget;
class USortButtonWidget;
//-----------------------------------------------------------------------------------------------------------
UCLASS()
class FPS_API UChestWidget : public UStorageWidget
{
	GENERATED_BODY()
public:
	virtual void InitStorageWidget(UStorageComponent* StorageComponent) override;
	void DeactivateAllTabsAnimation();
protected:
	virtual void NativeConstruct() override;

	UPROPERTY(BlueprintReadOnly, Category = "I_W", meta = (BindWidget)) USortButtonWidget* ButtonSortItemType;
	UPROPERTY(BlueprintReadOnly, Category = "I_W", meta = (BindWidget)) USortButtonWidget* ButtonSortItemGrade;
	UPROPERTY(BlueprintReadOnly, Category = "I_W", meta = (BindWidget)) USortButtonWidget* ButtonSortItemName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Chest Widget", meta = (BindWidget)) UScrollBox* TabsScrollBox;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Chest Widget") TSubclassOf<UStorageTabButtonWidget> WBPStorageTabButtonWidget;
	UPROPERTY() TArray<UStorageTabButtonWidget*> StorageTabButtonWidgetArray;
private:
};
//-----------------------------------------------------------------------------------------------------------