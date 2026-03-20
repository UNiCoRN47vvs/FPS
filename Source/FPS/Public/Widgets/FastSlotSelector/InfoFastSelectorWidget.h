#pragma once

#include "CoreMinimal.h"
#include "Widgets/Inventory/SlotWidget.h"
#include "Enums/ItemType.h"
#include "InfoFastSelectorWidget.generated.h"
//-----------------------------------------------------------------------------------------------------------
class UInventoryComponent;
class UProgressBar;
struct FItemInvStruct;
//-----------------------------------------------------------------------------------------------------------
UCLASS()
class FPS_API UInfoFastSelectorWidget : public USlotWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, Category = "I_F_S_W", meta = (BindWidget)) UProgressBar* CoolDownPB;
	UPROPERTY(BlueprintReadOnly, Category = "I_F_S_W", meta = (BindWidgetAnim), Transient) UWidgetAnimation* PushAnim;
	UPROPERTY(BlueprintReadOnly, Category = "I_F_S_W", meta = (BindWidgetAnim), Transient) UWidgetAnimation* CooldownAnim;
protected:
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;
	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	void UpdateInfoFastSelector(UItemMasterDA* itemMasterDA, const TArray<FItemInvStruct>& inventory);
	FORCEINLINE void Cooldown(const float currentTimeCoolDown, const float timeCooldown) noexcept;
	void PlayWidgetAnim();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "I_F_S_W") EItemType ItemType;
	UPROPERTY() UInventoryComponent* InventoryComponent;
};
