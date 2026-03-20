#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PopupActionMenuWidget.generated.h"
//-----------------------------------------------------------------------------------------------------------
class AFPSPlayerController;
class UInventoryButtonWidget;
class UHorizontalBox;
class UStorageComponent;
//-----------------------------------------------------------------------------------------------------------
UCLASS()
class FPS_API UPopupActionMenuWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	void SetData(int32 itemIndex, UStorageComponent* itemStorageComponent, AFPSPlayerController* itemPlayerController);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "P_A_M_W", meta = (BindWidget)) UInventoryButtonWidget* UseButton;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "P_A_M_W", meta = (BindWidget)) UInventoryButtonWidget* SellButton;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "P_A_M_W", meta = (BindWidget)) UInventoryButtonWidget* DestroyButton;
protected:
	virtual void NativeConstruct() override;
	virtual void NativeOnMouseEnter(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;
	virtual void NativeOnMouseLeave(const FPointerEvent& MouseEvent) override;

	UFUNCTION() void UseItem();
	UFUNCTION() void SellItem();
	UFUNCTION() void DestroyItem();

	int32 Index;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "P_A_M_W") USoundWave* SellSound;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "P_A_M_W") USoundWave* DestroySound;
	UPROPERTY() UStorageComponent* StorageComponent;
	UPROPERTY() AFPSPlayerController* PlayerController;
	UPROPERTY() FTimerHandle DestroyTimer;
private:
	void RemovePopupWidget();
};
//-----------------------------------------------------------------------------------------------------------