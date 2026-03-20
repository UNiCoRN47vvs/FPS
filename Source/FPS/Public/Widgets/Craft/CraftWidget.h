#pragma once

#include "Widgets/Inventory/StorageWidget.h"
#include "CraftWidget.generated.h"
//-----------------------------------------------------------------------------------------------------------
class UButton;
//-----------------------------------------------------------------------------------------------------------
UCLASS()
class FPS_API UCraftWidget : public UStorageWidget
{
	GENERATED_BODY()
public:
	virtual void InitStorageWidget(UStorageComponent* StorageComponent) override;
	void CraftEvent(bool bIsSuccess);

	UPROPERTY(BlueprintReadOnly, Category = "C_W", meta = (BindWidget)) UButton* CraftButton;
protected:
	UFUNCTION() void ClickCraftButton();

	UPROPERTY(BlueprintReadOnly, Category = "C_C", meta = (BindWidgetAnim), Transient) UWidgetAnimation* SuccessCraftAnimation;
	UPROPERTY(BlueprintReadOnly, Category = "C_C", meta = (BindWidgetAnim), Transient) UWidgetAnimation* FailCraftAnimation;
private:
};
//-----------------------------------------------------------------------------------------------------------