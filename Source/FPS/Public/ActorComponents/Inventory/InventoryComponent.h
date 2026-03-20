#pragma once

#include "ActorComponents/StorageComponent.h"
#include "InventoryComponent.generated.h"
//-----------------------------------------------------------------------------------------------------------
class UMainHUDWidget;
class UPlayerStateComponent;
//-----------------------------------------------------------------------------------------------------------
UCLASS(Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FPS_API UInventoryComponent : public UStorageComponent
{
	GENERATED_BODY()

public:	
	UInventoryComponent();
	
	bool DoesHasEmptySlots(int32  numberEmptySlots);
	virtual void ApplyFastDrop(AFPSPlayerController* Controller, int32 Index, UInventorySlotWidget* WidgetSlot) override;
	virtual bool PickUpItem(int32& itemCount, UItemMasterDA* itemDA, int32 itemLevel = 0, const FStatValueStruct statValueStruct = {}) override;
	virtual bool PickUpItem(const FCurrency& pickUpCurrency) override;
	UPlayerStateComponent* GetPlayerStateComponent();
	const FCurrency& GetCurrency();
	void SetCurrency(FCurrency Value);
	void SubtractCurrency(FCurrency Value);
	bool DoesHaveEnoughCurrency(FCurrency Price);
	bool DoesHaveEnoughItem(UItemMasterDA* ItemDataAsset, int32 Count);
	virtual void SetItemFromIndex(FItemInvStruct item, int32 indexTab, int32 indexStorage) override;

protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	void SelectPotion(UItemMasterDA* itemMasterDA);
	void SelectScroll(UItemMasterDA* itemMasterDA);
	void UseSelectedPotion();
	void UseSelectedScroll();
	void CoolDownTimer(FTimerHandle& timerHandle, bool& bIsCoolDown, float& timeCoolDown, float& currentTimeCoolDown);
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "I_C") USoundWave* DrinkPotionSound;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "I_C") USoundWave* CooldownSound;

	bool bIsPotionCooldown;
	float TimePotionCooldown;
	float CurrentTimePotionCooldown;
	FTimerHandle PotionTimer;

	bool bIsScrollCooldown;
	float TimeScrollCooldown;
	float CurrentTimeScrollCooldown;
	FTimerHandle ScrollTimer;
private:
	void UseScroll();
	UPROPERTY() UItemMasterDA* PotionDA;
	UPROPERTY() UItemMasterDA* ScrollDA;
	UPROPERTY() UPlayerStateComponent* PlayerStateComponent;
	int32 ScrollIndex;
};
//-----------------------------------------------------------------------------------------------------------
