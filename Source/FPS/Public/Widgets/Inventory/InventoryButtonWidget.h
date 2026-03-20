#pragma once

#include "FPS/FPS.h"
#include "Blueprint/UserWidget.h"
#include "InventoryButtonWidget.generated.h"
//-----------------------------------------------------------------------------------------------------------
class UButton;
class UTextBlock;
//-----------------------------------------------------------------------------------------------------------
UCLASS()
class FPS_API UInventoryButtonWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadOnly, Category = "Inventory Button Widget", meta = (BindWidget)) UButton* Button;
	UPROPERTY(BlueprintReadOnly, Category = "Inventory Button Widget", meta = (BindWidget)) UTextBlock* TextBlock;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Inventory Button Widget") FText Text;
protected:
	virtual void NativePreConstruct() override;
};
//-----------------------------------------------------------------------------------------------------------