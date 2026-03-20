#pragma once

#include "Widgets/Inventory/GenegalStorageWidget.h"
#include "Enums/ItemGrade.h"
#include "UpgradeWidget.generated.h"
//-----------------------------------------------------------------------------------------------------------
class UInventorySlotWidget;
class UProgressBar;
class UButton;
class UUpgradeComponent;
//-----------------------------------------------------------------------------------------------------------
USTRUCT(BlueprintType)
struct FGradeUpgradeChance : public FTableRowBase
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Grade Upgrade Chance") EItemGrade Grade;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Grade Upgrade Chance") float UpgradeChance;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Grade Upgrade Chance") float DowngradeChance;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Grade Upgrade Chance") float NothingChance;
};
//-----------------------------------------------------------------------------------------------------------
UCLASS()
class FPS_API UUpgradeWidget : public UGenegalStorageWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;
	virtual void UpdateSlots() override;
	void InitUpgradeWidget(UUpgradeComponent* StorageComponent);
	UPROPERTY(BlueprintReadOnly, Category = "U_W", meta = (BindWidget)) UInventorySlotWidget*  UpgradeSlot1;
	UPROPERTY(BlueprintReadOnly, Category = "U_W", meta = (BindWidget)) UInventorySlotWidget*  UpgradeSlot2;
	UPROPERTY(BlueprintReadOnly, Category = "U_W", meta = (BindWidget)) UProgressBar*  UpgradeProgressBar;
	UPROPERTY(BlueprintReadOnly, Category = "U_W", meta = (BindWidget)) UButton*  UpgradeButton;
	UPROPERTY(BlueprintReadOnly, Category = "U_W", meta = (BindWidgetAnim), Transient) UWidgetAnimation* UpgradeAnimation;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "U_W") USoundWave* UpgradingItemSound;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "U_W") USoundWave* UpgradingSuccessSound;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "U_W") USoundWave* UpgradingFailSound;
	uint8 bIsAnimationPlay : 1;
protected:
	UFUNCTION() void PushUpgradeButton();
	UFUNCTION() void UpgradeItem();
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Upgrade Widget") UDataTable* DTGradeUpgradeChance;
	UUpgradeComponent* UpgradeComponent;
};
//-----------------------------------------------------------------------------------------------------------