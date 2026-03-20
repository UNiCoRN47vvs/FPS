#pragma once

#include "FPS/FPS.h"
#include "Components/ActorComponent.h"
#include "Enums/ItemType.h"
#include "Enums/ItemGrade.h"
#include "Enums/StorageType.h"
#include "Enums/ElementsType.h"
#include "Struct/ItemInvStruct.h"
#include "Struct/CurrencyStruct.h"
#include "StorageComponent.generated.h"
//-----------------------------------------------------------------------------------------------------------
class AItemMaster;
class AFPSPlayerController;
class AFPSCharacter;
class UInventorySlotWidget;
class UMainHUDWidget;
class UItemMasterDA;
struct FStatValueStruct;
//-----------------------------------------------------------------------------------------------------------
USTRUCT(BlueprintType)
struct FStorageTab
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Storage") TArray<FItemInvStruct> StorageTab = {};
};
//-----------------------------------------------------------------------------------------------------------
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPickUpItem);
//-----------------------------------------------------------------------------------------------------------
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FPS_API UStorageComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UStorageComponent();
	virtual void InitArmorStat();
	virtual void RefreshMagazine(int32 index);
	const TArray<FItemInvStruct>& GetStorage();
	const TArray<FStorageTab>& GetAllStorageTabs();
	EStorageType GetStorageType();
	bool IsStorageEmpty();

	virtual bool PickUpItem(int32& itemCount, UItemMasterDA* itemDA, int32 itemLevel = 0, const FStatValueStruct statValueStruct = {});
	virtual bool PickUpItem(const FCurrency& pickUpCurrency);
	virtual void SetItemFromIndex(FItemInvStruct item, int32 indexTab, int32 indexStorage);
	virtual void ApplyFastDrop(AFPSPlayerController* controller, int32 index, UInventorySlotWidget* widgetSlot);
	void InitStorage();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "S_C") int32 InvMaxSlots;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "S_C") int32 InvSlotsPerRow;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "S_C") int32 InvMaxTabs;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "S_C") int32 CurrentActiveInvTab;
	UPROPERTY(BlueprintAssignable, Category = "S_C") FOnPickUpItem OnPickUpItem;
protected:
	virtual void BeginPlay() override;
	virtual void OnComponentDestroyed(bool bDestroyingHierarchy) override;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "S_C") EStorageType StorageType;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "S_C") TArray<FStorageTab> Storage;
	UPROPERTY() AFPSPlayerController* PlayerController;
	UPROPERTY() AFPSCharacter* PlayerCharacter;
	UPROPERTY() UMainHUDWidget* MainHUDWidget;
	EStorageType FastDropStorage;
	FCurrency Currency;
	
private:
};
//-----------------------------------------------------------------------------------------------------------