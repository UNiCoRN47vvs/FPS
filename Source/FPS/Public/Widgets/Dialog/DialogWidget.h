
#pragma once

#include "FPS/FPS.h"
#include "Blueprint/UserWidget.h"
#include "DialogWidget.generated.h"
//-----------------------------------------------------------------------------------------------------------
class UButton;
class UStorageComponent;
class UMainHUDWidget;
class UInventoryButtonWidget;
//-----------------------------------------------------------------------------------------------------------
UCLASS()
class FPS_API UDialogWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	void InitDialogWidget(UStorageComponent* storageComp, UMainHUDWidget* mainHUDWidget);
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "D_W", meta = (BindWidget)) UInventoryButtonWidget* BuyButton;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "D_W", meta = (BindWidget)) UInventoryButtonWidget* QuestButton;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "D_W", meta = (BindWidget)) UInventoryButtonWidget* CloseButton;
private:
	UFUNCTION() void ApplyBuyButton();
	UFUNCTION() void ApplyQuestButton();
	UFUNCTION() void ApplyCloseButton();

	TWeakObjectPtr<UStorageComponent> StorageComponent;
	TWeakObjectPtr<UMainHUDWidget> MainHUD;
};
//-----------------------------------------------------------------------------------------------------------