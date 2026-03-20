#include "ActorComponents/Equipment/EquipmentComponent.h"
#include "Engine/World.h"
#include "Engine/StreamableManager.h"
#include "Engine/AssetManager.h"
#include "Kismet/GameplayStatics.h"
#include "SubSystem/EventBus.h"
#include "FPS/FPSCharacter.h"
#include "Animation/AnimFirstPerson.h"
#include "ActorComponents/Inventory/InventoryComponent.h"
#include "ActorComponents/Equipment/EquipmentComponent.h"
#include "Widgets/Inventory/InventorySlotWidget.h"
#include "Items/Weapons/WeaponMaster.h"
#include "Items/Weapons/MagazineMaster.h"
#include "Items/Armor/ArmorMaster.h"
#include "Config/AudusMasterDA.h"
#include "Struct/StatValueStruct.h"
//-----------------------------------------------------------------------------------------------------------
UEquipmentComponent::UEquipmentComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	bMontageIsActive = false;
	AudusIndex = 1;
}
//-----------------------------------------------------------------------------------------------------------
void UEquipmentComponent::BeginPlay()
{
	Super::BeginPlay();
	PlayerCharacter = Cast<AFPSCharacter>(GetOwner());
	if (!IsValid(PlayerCharacter->GetMesh1P()->GetAnimInstance()))
	{
		ALARM_LOG
		return;
	}

	UAnimFirstPerson* animInstance = Cast<UAnimFirstPerson>(PlayerCharacter->GetMesh1P()->GetAnimInstance());
	CHECK_PTR(animInstance)

	animInstance->InitAnimInstance(this);
	PlayerCharacter->OnEquipWeapon.BindUObject(this, &UEquipmentComponent::ToggleEquipWeapon);
	PlayerCharacter->OnActivateAudus.BindUObject(this, &UEquipmentComponent::ActivateAudus);

	UEventBus::OnGeneralWidgetClose.AddUObject(this, &UEquipmentComponent::CheckStaff);
}
//-----------------------------------------------------------------------------------------------------------
void UEquipmentComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	CHECK_CAST(PlayerCharacter, AFPSCharacter, GetOwner())

	PlayerCharacter->OnEquipWeapon.Unbind();
	PlayerCharacter->OnActivateAudus.Unbind();
	UEventBus::OnGeneralWidgetClose.RemoveAll(this);
}
//-----------------------------------------------------------------------------------------------------------
FStatValueStruct UEquipmentComponent::GetWeaponsStat()
{
	FStatValueStruct weaponsStat = {};

	if (GetStorage()[0].bOccupied)
		CombineWeaponsStat(GetStorage()[0].StatValue.StatsValue, weaponsStat);
	
	if(!GetStorage().IsValidIndex(AudusIndex))
		return weaponsStat;

	CombineWeaponsStat(GetStorage()[AudusIndex].StatValue.StatsValue, weaponsStat);

	return weaponsStat;
}
//-----------------------------------------------------------------------------------------------------------
void UEquipmentComponent::CombineWeaponsStat(const TMap<EStateName, float>& slotStat, FStatValueStruct& weaponsStat)
{
	for (const auto& item : slotStat)
	{
		if (weaponsStat.StatsValue.Contains(item.Key))
			*weaponsStat.StatsValue.Find(item.Key) += item.Value;
		else
			weaponsStat.StatsValue.Add(item);
	}
}
//-----------------------------------------------------------------------------------------------------------
void UEquipmentComponent::InitArmorStat()
{
	Super::InitArmorStat();

	FStatValueStruct armorStat = {};
	FItemInvStruct itemStruct = {};

	for (int32 i = 0; i < GetStorage().Num(); ++i)
	{
		if (!GetStorage()[i].bOccupied 
			|| !GetStorage()[i].ItemDA 
			|| GetStorage()[i].ItemDA->ItemType == EItemType::Audus ? i != AudusIndex : false
			|| GetStorage()[i].ItemDA->ItemType == EItemType::MagicMagazine)
			continue;		

		itemStruct = GetStorage()[i];
		for (const auto& item : itemStruct.GetItemStatFromLevel())
		{
			if (armorStat.StatsValue.Contains(item.Key))
				*armorStat.StatsValue.Find(item.Key) += item.Value;
			else
				armorStat.StatsValue.Add(item);
		}

		for (const auto& item : itemStruct.StatValue.StatsValue)
		{
			if (armorStat.StatsValue.Contains(item.Key))
				*armorStat.StatsValue.Find(item.Key) += item.Value;
			else
				armorStat.StatsValue.Add(item);
		}
	}
	OnChangeEquipStat.ExecuteIfBound(armorStat);
	armorStat = {};
}
//-----------------------------------------------------------------------------------------------------------
void UEquipmentComponent::RefreshMagazine(int32 Index)
{
	int32 index = 0;
	EItemType itemType = EItemType::All;
	if (Index != 1)
		return;

	CHECK_PTR(GetStorage()[Index].ItemDA)

	switch (GetStorage()[Index].ItemDA->ItemType)
	{
	case EItemType::MagicWeapon :
		PickUpItem(MagicWeaponMagazine.CurrentAmmo, MagicWeaponMagazine.MagazineDA);
		MagicWeaponMagazine = {};
		itemType = EItemType::MagicMagazine;
		break;

	default:
		break;
	}

	for (int32 i = 0; i < GetStorage().Num(); i++)
	{
		if (GetStorage()[i].ItemDA && GetStorage()[i].ItemDA->ItemType == itemType)
		{
			index = i;
			break;
		}
	}

	UEventBus::OnSetItemFromIndexWidget.ExecuteIfBound(StorageType, index, GetStorage());
}
const FMagazine& UEquipmentComponent::GetMagicMagazine()
{
	return MagicWeaponMagazine;
}
FMagazine& UEquipmentComponent::GetActiveMagazine()
{
	return MagicWeaponMagazine;
}
FItemInvStruct UEquipmentComponent::GetActiveAudus()
{
	return GetStorage()[AudusIndex];
}
FItemInvStruct UEquipmentComponent::GetActiveWeapon()
{
	return GetStorage()[0];
}
void UEquipmentComponent::SetMagazines(const FMagazine& MagicMagazine)
{
	MagicWeaponMagazine = MagicMagazine;
}
//-----------------------------------------------------------------------------------------------------------
void UEquipmentComponent::InitEquipmentSlots(const TArray<UInventorySlotWidget*>& WidgetsArray)
{
	for (const UInventorySlotWidget* widget : WidgetsArray)
	{
		SlotsItemType.Add(widget->Index, widget->SlotType);
	}
}
//-----------------------------------------------------------------------------------------------------------
// Логика экипировки оружия
void UEquipmentComponent::ToggleEquipWeapon(int32 WeaponIndex)
{
	UWeaponMasterDA* weaponDA = nullptr;
	USkeletalMeshComponent* skeletalMesh = nullptr;
	EItemType itemType = EItemType::All;
	FItemInvStruct weaponInIndex = GetStorage()[WeaponIndex];
	FTransform spawnTransform = FTransform(FRotator::ZeroRotator, GetOwner()->GetActorLocation());

	if (bMontageIsActive)
		return;
	CHECK_CAST(PlayerCharacter, AFPSCharacter, GetOwner())

	// Логика удаления текущего оружия и экипировки нового
	if (ActiveWeapon)
	{
		itemType = ActiveWeapon->GetItemInfo().ItemType;
		RifleStateDelegate.ExecuteIfBound(false, itemType);
		ActiveWeapon->Destroy();
		ActiveWeapon = nullptr;
		UEventBus::OnUpdateAmmoWidget.ExecuteIfBound(0, 0);

		if (GetStorage()[WeaponIndex].ItemDA && itemType != GetStorage()[WeaponIndex].ItemDA->ItemType)
			ToggleEquipWeapon(WeaponIndex);
	}
	else
	{
		CHECK_PTR(weaponInIndex.ItemDA)
		weaponDA = Cast<UWeaponMasterDA>(weaponInIndex.ItemDA);
		CHECK_PTR(weaponDA)

		if (!weaponDA->ItemClass.ToSoftObjectPath().ResolveObject())
		{
			UAssetManager::GetStreamableManager().RequestAsyncLoad(weaponDA->ItemClass.ToSoftObjectPath(), [this, WeaponIndex, weaponDA]()
				{
					if (weaponDA->ItemClass.LoadSynchronous())
					{
						AsyncTask(ENamedThreads::GameThread, [this, WeaponIndex]()
							{
								ToggleEquipWeapon(WeaponIndex);
							});
					}
				});
			return;
		}
		skeletalMesh = PlayerCharacter->GetMesh1P();

		ActiveWeapon = GetWorld()->SpawnActorDeferred<AWeaponMaster>(weaponDA->ItemClass.Get(), spawnTransform);
		
		CHECK_PTR(ActiveWeapon)
		CHECK_PTR(skeletalMesh)

		ActiveWeapon->InitParams(weaponDA);
		ActiveWeapon->Tags.Add(FName(TEXT("NotInteractable")));

		ActiveWeapon->InitParamsActiveWeapon(skeletalMesh, weaponInIndex.ItemLevel, this);
		UGameplayStatics::FinishSpawningActor(ActiveWeapon, spawnTransform);

		FMagazine& magazine = GetActiveMagazine();

		// Логика работы с магазинами для оружия
		if(magazine.MagazineDA)
			UEventBus::OnUpdateAmmoWidget.ExecuteIfBound(magazine.CurrentAmmo, weaponDA->UseValue);
		
		// Анимация экипировки оружия
		if (weaponDA->AnimationEquipWeapon.LoadSynchronous() && skeletalMesh->GetAnimInstance())
		{
			AnimInstance = skeletalMesh->GetAnimInstance();
			AnimInstance->Montage_Play(weaponDA->AnimationEquipWeapon.Get());
			AnimInstance->OnMontageEnded.AddDynamic(this, &UEquipmentComponent::EquipWeaponMontageEnded);
			bMontageIsActive = true;
		}
	}
}
//-----------------------------------------------------------------------------------------------------------
void UEquipmentComponent::ActivateAudus(int32 audusIndex)
{
	AudusIndex = audusIndex;
	InitArmorStat();

	if(GetStorage().IsValidIndex(audusIndex))
		UEventBus::OnActivateAudus.ExecuteIfBound(GetStorage()[audusIndex].ItemDA);
}
//-----------------------------------------------------------------------------------------------------------
void UEquipmentComponent::CheckStaff()
{
	CHECK_CAST(PlayerCharacter, AFPSCharacter, GetOwner())

	if (ActiveWeapon && ActiveWeapon->GetConfigDA<UItemMasterDA>() != GetActiveWeapon().ItemDA)
	{
		ToggleEquipWeapon(0);
		PlayerCharacter->PickUpItem(MagicWeaponMagazine.CurrentAmmo, MagicWeaponMagazine.MagazineDA);
	}

	if (GetStorage().IsValidIndex(AudusIndex))
		UEventBus::OnActivateAudus.ExecuteIfBound(GetStorage()[AudusIndex].ItemDA);

}
//-----------------------------------------------------------------------------------------------------------
void UEquipmentComponent::EquipWeaponMontageEnded(UAnimMontage* Montage, bool bInterrupted)
{
	AnimInstance->OnMontageEnded.RemoveDynamic(this, &UEquipmentComponent::EquipWeaponMontageEnded);
	RifleStateDelegate.ExecuteIfBound(true, ActiveWeapon->GetItemInfo().ItemType);
	bMontageIsActive = false;
}
//-----------------------------------------------------------------------------------------------------------
void UEquipmentComponent::ReloadMagazine()
{
	bool bMagazineFound = false;
	UWeaponMasterDA* weaponDA = nullptr;
	UAnimMontage* shootMontage = nullptr;
	UAnimMontage* reloadMontage = nullptr;
	UInventoryComponent* inventoryComponent = nullptr;
	EElementsType elementsType = EElementsType::None;
	int32 slotIndex = 0;
	FItemInvStruct item = {};

	CHECK_CAST(PlayerCharacter, AFPSCharacter, GetOwner())

	if (!PlayerCharacter->GetMesh1P() || !IsValid(PlayerCharacter->GetMesh1P()->GetAnimInstance()) || !IsValid(ActiveWeapon))
	{
		ALARM_LOG
		return;
	}

	if (PlayerCharacter->bIsReload || ActiveWeapon->bIsReloading)
		return;


	weaponDA = ActiveWeapon->GetConfigDA<UWeaponMasterDA>();
	CHECK_PTR(weaponDA)
	
	inventoryComponent = PlayerCharacter->GetInventoryComponent();
	CHECK_PTR(inventoryComponent)

	const TArray<FItemInvStruct>& inventory = inventoryComponent->GetStorage();

	for (const auto& elem : SlotsItemType)
	{
		if (elem.Value == weaponDA->MagazineTypeForWeapon)
		{
			slotIndex = elem.Key;
			break;
		}
	}

	if (GetStorage()[slotIndex].bOccupied && GetStorage()[slotIndex].ItemDA && GetStorage()[slotIndex].ItemDA->ItemType == weaponDA->MagazineTypeForWeapon) //Проверка наличия магазина в ячейке для магазина
		bMagazineFound = true;

	if (!bMagazineFound) // Если магазин не найден, проверяем инвентарь и пытаемся добавить его в хранилище
	{
		for (int32 j = 0; j < inventory.Num(); ++j)
		{
			if (!inventory[j].ItemDA || inventory[j].ItemDA && inventory[j].ItemDA->ItemType != weaponDA->MagazineTypeForWeapon) //Проверка на различие типов предмета 
				continue;

			item = Storage[CurrentActiveInvTab].StorageTab[slotIndex];
			Storage[CurrentActiveInvTab].StorageTab[slotIndex] = inventory[j];
			elementsType = inventory[j].ItemDA->ElementType;
			inventoryComponent->SetItemFromIndex(item, inventoryComponent->CurrentActiveInvTab, j);
			
			CHECK_PTR(inventory[slotIndex].ItemDA)
			CHECK_PTR(GetStorage()[slotIndex].ItemDA)

			const int32 summ = GetStorage()[slotIndex].ItemCount + inventory[j].ItemCount;

			if (GetStorage()[slotIndex].ItemCount == GetStorage()[slotIndex].ItemDA->ItemCountMax) // Проверка текущее колличество равно ли максимальному
				break;

			if (summ > GetStorage()[slotIndex].ItemDA->ItemCountMax) //Если больше то узнаем разницу и пременяем её для вычета
			{
				const int32 subtract = GetStorage()[slotIndex].ItemDA->ItemCountMax - GetStorage()[slotIndex].ItemCount;
				item = inventory[j];
				item.ItemCount -= subtract;
				Storage[CurrentActiveInvTab].StorageTab[slotIndex].ItemCount = GetStorage()[slotIndex].ItemDA->ItemCountMax;
				break;
			}
			Storage[CurrentActiveInvTab].StorageTab[slotIndex].ItemCount += inventory[j].ItemCount;
			inventoryComponent->SetItemFromIndex(item, inventoryComponent->CurrentActiveInvTab, j);
		}

		if (!GetStorage()[slotIndex].bOccupied) // Если в хранилище так и не оказалось магазина, возвращаемся и показываем сообщение "Нет патронов"
			return; // TODO: Добавить виджет с надписью "Нет патронов"!!!!!!!!!!!!!!
	}

	shootMontage = ActiveWeapon->AnimationShoot;
	reloadMontage = weaponDA->AnimationReloadWeapon;

	AnimInstance = PlayerCharacter->GetMesh1P()->GetAnimInstance();
	CHECK_PTR(AnimInstance)

	ActiveWeapon->StartReload(true);
	PlayerCharacter->bIsReload = true;

	if (shootMontage && reloadMontage && !AnimInstance->Montage_IsPlaying(reloadMontage))
	{
		AnimInstance->OnMontageEnded.RemoveDynamic(this, &UEquipmentComponent::RealoadMagazineAfterMontage);
		AnimInstance->Montage_Play(reloadMontage);
		AnimInstance->OnMontageEnded.AddDynamic(this, &UEquipmentComponent::RealoadMagazineAfterMontage);
	}
}
//-----------------------------------------------------------------------------------------------------------
void UEquipmentComponent::RealoadMagazineAfterMontage(UAnimMontage* montage, bool bInterrupted)
{
	UItemMasterDA* itemDA = nullptr;
	UWeaponMasterDA* weaponDA = nullptr;
	UMagazineMasterDA* magazineDA = nullptr;
	UInventoryComponent* inventoryComponent = nullptr;
	FItemInvStruct magazine = {};
	int32 storageSize = Storage[CurrentActiveInvTab].StorageTab.Num();
	FMagazine& activeMagazine = GetActiveMagazine();

	CHECK_PTR(ActiveWeapon)
	weaponDA = ActiveWeapon->GetConfigDA<UWeaponMasterDA>();
	CHECK_PTR(weaponDA)

	if (montage != weaponDA->AnimationReloadWeapon)
		return;

	AnimInstance->OnMontageEnded.RemoveDynamic(this, &UEquipmentComponent::RealoadMagazineAfterMontage);

	CHECK_CAST(PlayerCharacter, AFPSCharacter, GetOwner())
	
	inventoryComponent = PlayerCharacter->GetInventoryComponent();
	CHECK_PTR(inventoryComponent)

	CHECK_PTR(ActiveWeapon)

	float LocalAmmoUse = weaponDA->UseValue;

	for (int32 i = 0; i < storageSize; ++i)
	{
		FItemInvStruct& item = Storage[CurrentActiveInvTab].StorageTab[i];

		if (!item.bOccupied || !item.ItemDA || item.ItemDA->ItemType != weaponDA->MagazineTypeForWeapon)
			continue;
		
		if (ActiveWeapon && activeMagazine.MagazineDA)
		{
			magazineDA = activeMagazine.MagazineDA;
			CHECK_PTR(magazineDA)
			
			if(item.ItemDA->ElementType == magazineDA->ElementType)
				item.ItemCount += activeMagazine.CurrentAmmo;
			else
				inventoryComponent->PickUpItem(activeMagazine.CurrentAmmo, magazineDA);
			
			activeMagazine = {};
		}

		itemDA = item.ItemDA;

		if (itemDA->ItemClass.Get())
			RealoadMagazineAfterMontageSubFunc(item, LocalAmmoUse, i, itemDA->ItemClass);
		else
		{
			UAssetManager::GetStreamableManager().RequestAsyncLoad(itemDA->ItemClass.ToSoftObjectPath(), [this, itemDA, item, LocalAmmoUse, i]()
				{
					if (itemDA->ItemClass.LoadSynchronous())
					{
						AsyncTask(ENamedThreads::GameThread, [this, itemDA, item, LocalAmmoUse, i]()
							{
								RealoadMagazineAfterMontageSubFunc(item, LocalAmmoUse, i, itemDA->ItemClass);
							});
					}
				});
		}

		return;
	}
}
//-----------------------------------------------------------------------------------------------------------
void UEquipmentComponent::RealoadMagazineAfterMontageSubFunc(FItemInvStruct Item, int32 AmmoUse, int32 Index, TSoftClassPtr<AItemMaster> ItemClass)
{
	UWeaponMasterDA* weaponDA = nullptr;
	UMagazineMasterDA* magazineDA = nullptr;
	FMagazine magazine = {};
	int32 itemCount = Item.ItemCount - AmmoUse;
	CHECK_PTR(Item.ItemDA)

	magazineDA = Cast<UMagazineMasterDA>(Item.ItemDA);
	CHECK_PTR(magazineDA)

	weaponDA = ActiveWeapon->GetConfigDA<UWeaponMasterDA>();
	CHECK_PTR(weaponDA)

	switch (weaponDA->MagazineTypeForWeapon)
	{

	case EItemType::MagicMagazine:
		MagicWeaponMagazine.MagazineDA = magazineDA;
		Item.ItemCount < AmmoUse ? MagicWeaponMagazine.CurrentAmmo = Item.ItemCount : MagicWeaponMagazine.CurrentAmmo = AmmoUse;
		magazine = MagicWeaponMagazine;
		break;

	default:
		break;
	}

	if (itemCount > 0)
	{
		Item.ItemCount -= AmmoUse;
		SetItemFromIndex(Item, CurrentActiveInvTab, Index);
		ActiveWeapon->WeaponReload(this);
	}
	else
	{
		SetItemFromIndex(FItemInvStruct{}, CurrentActiveInvTab, Index);
		ActiveWeapon->WeaponReload(this);
	}
	UEventBus::OnUpdateAmmoWidget.ExecuteIfBound(magazine.CurrentAmmo, AmmoUse);
	ActiveWeapon->bIsReloading = false;

	CHECK_CAST(PlayerCharacter, AFPSCharacter, GetOwner())

	PlayerCharacter->bIsReload = false;
}

