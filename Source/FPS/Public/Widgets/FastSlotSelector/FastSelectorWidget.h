#pragma once

#include "FPS/FPS.h"
#include "Blueprint/UserWidget.h"
#include "FastSelectorWidget.generated.h"
//-----------------------------------------------------------------------------------------------------------
class USlotWidget;
class UVerticalBox;
class UWidgetSwitcher;
class UInventoryComponent;
class UFastSelectorIconWidget;
class UPotionMasterDA;
class USkillScrollDA;
class UFastSelectorBlockWidget;
class UFastSelectorItemSlotWidget;
//-----------------------------------------------------------------------------------------------------------
struct FPotionStruct
{
	int32 PotionCount;
	UPotionMasterDA* PotionDA;
};
//-----------------------------------------------------------------------------------------------------------
struct FScrollStruct
{
	int32 ScrollCount;
	USkillScrollDA* ScrollDA;
};
//-----------------------------------------------------------------------------------------------------------
UCLASS()
class FPS_API UFastSelectorWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadOnly, Category = "F_S_W", meta = (BindWidget)) UVerticalBox* PotionVB;
	UPROPERTY(BlueprintReadOnly, Category = "F_S_W", meta = (BindWidget)) UVerticalBox* ScrollVB;
	UPROPERTY(BlueprintReadOnly, Category = "F_S_W", meta = (BindWidget)) UWidgetSwitcher* PotionWidgetSwitcher;
	UPROPERTY(BlueprintReadOnly, Category = "F_S_W", meta = (BindWidget)) UWidgetSwitcher* ScrollWidgetSwitcher;
protected:
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;
	void ShowHideWidget(bool bIsShow);
	void InitPotionWidgets(TMap<FName, FPotionStruct>& potionsMap, TArray<FPotionStruct>& potionsArray);
	void InitSkillsWidgets(TMap<FName, FScrollStruct>& scrollsMap, TArray<FScrollStruct>& scrollsArray);
	void SelectorIconClickPotion(int32 index);
	void SelectorIconClickScroll(int32 index);
	void GetPotionsAndScrolls(TMap<FName, FPotionStruct>& potionsMap, TArray<FPotionStruct>& potionsArray, TMap<FName, FScrollStruct>& scrollsMap, TArray<FScrollStruct>& scrollsArray);
	UInventoryComponent* GetInventoryComponent();
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "F_S_W") TSubclassOf<UFastSelectorItemSlotWidget> ItemSlotClass;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "F_S_W") TSubclassOf<UFastSelectorBlockWidget> SelectorBlockClass;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "F_S_W") TSubclassOf<UFastSelectorIconWidget> FastSelectorIconClass;
 
	UPROPERTY() APlayerController* Controller;
	UPROPERTY() UInventoryComponent* InventoryComponent;
};
//-----------------------------------------------------------------------------------------------------------