#pragma once

#include "ActorComponents/StorageComponent.h"
#include "Enums/ItemType.h"
#include "Enums/FiringMode.h"
#include "Struct/MagazineStruct.h"
#include "Struct/StatRange.h"
#include "Struct/StatStruct.h"
#include "EquipmentComponent.generated.h"
//-----------------------------------------------------------------------------------------------------------
class AWeaponMaster;
class AMagazineMaster;
class UInventoryComponent;
class UInventorySlotWidget;
class UAudusMasterDA;
struct FArmorStat;
struct FStatValueStruct;
//-----------------------------------------------------------------------------------------------------------
UCLASS(Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FPS_API UEquipmentComponent : public UStorageComponent
{
	GENERATED_BODY()

public:	
	UEquipmentComponent();
	virtual void InitArmorStat() override;
	virtual void RefreshMagazine(int32 Index) override;
	const FMagazine& GetMagicMagazine();
	FMagazine& GetActiveMagazine();
	FItemInvStruct GetActiveAudus();
	FItemInvStruct GetActiveWeapon();
	void SetMagazines(const FMagazine& MagicMagazine);
	void InitEquipmentSlots(const TArray<UInventorySlotWidget*>& WidgetsArray);
	UFUNCTION() void ToggleEquipWeapon(int32 WeaponIndex);
	void ReloadMagazine();

	TDelegate<void(const FStatValueStruct&)> OnChangeEquipStat;
	TDelegate<void(bool, EItemType)> RifleStateDelegate;
	UPROPERTY() AWeaponMaster* ActiveWeapon;

protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	FStatValueStruct GetWeaponsStat();
	void CombineWeaponsStat(const TMap<EStateName, float>& slotStat, FStatValueStruct& weaponsStat);
	UPROPERTY() UAnimInstance* AnimInstance;
	UPROPERTY() FMagazine MagicWeaponMagazine;
	int32 AudusIndex;
private:
	void ActivateAudus(int32 audusIndex);
	void CheckStaff();
	UFUNCTION() void EquipWeaponMontageEnded(UAnimMontage* Montage, bool bInterrupted);
	UFUNCTION() void RealoadMagazineAfterMontage(UAnimMontage* montage, bool bInterrupted);
	UFUNCTION() void RealoadMagazineAfterMontageSubFunc(FItemInvStruct Item, int32 AmmoUse, int32 Index, TSoftClassPtr<AItemMaster> ItemClass);

	uint8 bMontageIsActive : 1;
	TMap<int32 ,EItemType> SlotsItemType;
};
//-----------------------------------------------------------------------------------------------------------