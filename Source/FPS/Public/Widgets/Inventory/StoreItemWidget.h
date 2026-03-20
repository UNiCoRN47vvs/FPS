#pragma once

#include "FPS/FPS.h"
#include "Blueprint/UserWidget.h"
#include "StoreItemWidget.generated.h"
//-----------------------------------------------------------------------------------------------------------
class UWrapBox;
class UButton;
class UTextBlock;
class UInventorySlotWidget;
class UNPCStorageComponent;
class AFPSCharacter;
//-----------------------------------------------------------------------------------------------------------
UCLASS()
class FPS_API UStoreItemWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	void InitStoreItemWidget(UNPCStorageComponent* storageComponent, int32 itemIndex);

	UPROPERTY(BlueprintReadOnly, Category = "S_I_W", meta = (BindWidget)) UWrapBox* WrapBox;
	UPROPERTY(BlueprintReadOnly, Category = "S_I_W", meta = (BindWidget)) UButton* BuyButton;
	UPROPERTY(BlueprintReadOnly, Category = "S_I_W", meta = (BindWidget)) UTextBlock* TextBlock;
	UPROPERTY(BlueprintReadOnly, Category = "S_I_W", meta = (BindWidget)) UInventorySlotWidget* ProductWidget;
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "S_I_W") USoundWave* BuySound;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "S_I_W") USoundWave* NoMoneySound;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "S_I_W") TSubclassOf<UInventorySlotWidget> PriceItemWidgetClass;
private:
	UFUNCTION() void BuyItem();

	UPROPERTY() UNPCStorageComponent* StorageComponent;
	UPROPERTY() AFPSCharacter* PlayerCharacter;

	int32 ItemIndex;
};
//-----------------------------------------------------------------------------------------------------------